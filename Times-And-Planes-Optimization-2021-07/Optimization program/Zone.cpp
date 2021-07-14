//
// Created by Антон on 07.07.2021.
//
#include <iostream>
#include "Zone.h"
#include "gurobi_c++.h"
#include <iomanip>

using namespace std;

Zone &Zone::get_instance()
{
  // The only instance of the class is created at the first call get_instance()
  // and will be destroyed only when the program exits
  static Zone instance;
  return instance;
}

Zone zone = Zone::get_instance();

struct Point;
bool isIn(const std::map<int, int> &m, const int key, int &HA_ID);
void print_(vector<Point> &grb_points);

void print_Zone()
{
  cout << "Descendant graph: \t\tAncestor graph:" << endl;
  for (int i = 0; i < zone.graph.size(); ++i)
  {
    int j = zone.graph.size() - 1 - i;
    
    cout << zone.checkPoints[i].name << " --> ";
    for (auto el : zone.graph[i])
    {
      cout << zone.checkPoints[el].name << " ";
    }
    cout << "\t\t\t";
    cout << zone.checkPoints[i].name << " --> ";
    for (auto el : zone.ancestors_graph[i])
    {
      cout << zone.checkPoints[el].name << " ";
    }
    cout << endl;
  }
  cout << endl;
}
//Процедура работает с конца
void calc_best_trajectory(std::vector<std::map<int, int>> &trjs, const int point_to_reach, const int current_point)
{
  static std::map<int, int> trj{};
  const static int end_point = current_point;
  if (current_point == point_to_reach)
  {
    //estimate trj
    trjs.push_back(trj);
    
    if (isBetter(trj, 0, 0, 0, 0, 0))
      zone.best_trj = trj;
  }
  else
  {
    for (const auto parent : zone.ancestors_graph.at(current_point))
    {
      trj.insert({parent, current_point});
      calc_best_trajectory(trjs, point_to_reach, parent);
      trj.erase(parent);
    }
  }
}

void i2s(int n, int l, string &s)
{
  stringstream ss;
  ss << setw(l) << setfill('0') << n;
  s = ss.str();
}

GRBLinExpr obj_func{0};

class Point
{
  public:
    int ID;
    GRBVar t;
    GRBVar tpr; //Время прихода в точку начала ЗО
    GRBVar v;
    GRBVar S;
    GRBVar nu;
    GRBVar chi;
    
  
private:
static void process_linear_segment(GRBModel &model, Point &curr, const Point &pred, double S_edge, const string &numS)
{
  
  curr.t = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "t" + numS);
  curr.v = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "v" + numS);
  curr.S = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "S" + numS);
  curr.chi = model.addVar(0, 1, 0, GRB_BINARY, "chi" + numS);
  
  obj_func += curr.chi;
  
  double v_min{zone.checkPoints.at(curr.ID).V_min.meters_per_second};
  double v_max{zone.checkPoints.at(curr.ID).V_max.meters_per_second};
  model.addConstr(v_min <= curr.v);
  model.addConstr(v_max >= curr.v);
  
  model.addConstr(curr.S == S_edge);
  
  model.addQConstr((1 - curr.chi)*pred.v + curr.chi*v_min, GRB_LESS_EQUAL, curr.v);
  model.addQConstr((1 - curr.chi)*pred.v + curr.chi*v_max, GRB_GREATER_EQUAL, curr.v);
  model.addQConstr(2*curr.S, GRB_EQUAL, (curr.v + pred.v)*(curr.t - pred.t));
}

public:
    static Point create_LPoint(GRBModel &model, int ID, const Point &pred, double S_edge)
    {
      Point p;
      p.ID = ID;
  
      string numS;
      i2s(ID, 2, numS);
      process_linear_segment(model, p, pred, S_edge, numS);
      return p;
    }

    static Point create_HAPoint(GRBModel &model, int ID, const Point &pred, const HoldingArea &ha)
    {
      Point p;
      p.ID = ID;
      
      string numS;
      i2s(ID, 2, numS);
      numS += "HA";
  
      double S_edge = distance(zone.checkPoints.at(pred.ID), zone.checkPoints.at(p.ID)).m();
      process_linear_segment(model, p , pred, S_edge, numS);
      
      p.tpr = p.t;
      
      p.t = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "t" + numS);
      
      
      model.addConstr(p.tpr + ha.t_min.s() <= p.t);
      model.addConstr(p.tpr + ha.t_max.s() >= p.t);
      
      
      return p;
    };
};

bool isBetter(const std::map<int, int> &trj, int start_point, int end_point, double t0, double v0, double tEnd)
{
  GRBEnv *env = new GRBEnv();
  GRBModel model = GRBModel(*env);
  
  Point grb_start_point;
  grb_start_point.t = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "t00");
  grb_start_point.v = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "v00");
  
  model.addConstr(grb_start_point.t == t0); //s
  model.addConstr(grb_start_point.v == v0); //m_s
  
  obj_func = GRBLinExpr(0);
  int cInter{0};
  vector<Point> grb_points{grb_start_point};
  int predID{start_point};
  int currID;
  do
  {
    currID = trj.at(predID);
    //Обработка ЗО
    int HA_ID{-1};
    if (isIn(zone.point_to_HA, currID, HA_ID))
    {
      grb_points.push_back(Point::create_HAPoint(model, currID, grb_points.back(), zone.holdingAreas.at(HA_ID)));
      predID = currID;
      cInter++; //Взаимодействие на уход на ЗО
    }
    else //Линейный участок
    {
      CheckPoint pred = zone.checkPoints.at(predID);
      CheckPoint current = zone.checkPoints.at(currID);
      grb_points.push_back(Point::create_LPoint(model, currID, grb_points.back(), distance(pred, current).m()));//m
      predID = currID;
    }
  }
  while (currID != end_point);
  
  model.addConstr(grb_points.back().t == tEnd);
  
  obj_func += cInter;
  model.setObjective(obj_func, GRB_MINIMIZE);
  
  model.set(GRB_IntParam_Threads, 6);
  model.set(GRB_IntParam_NonConvex, 2);
  model.optimize();
  
  
  print_(grb_points);
  
  
  return true;
}

bool isIn(const std::map<int, int> &m, const int key, int &HA_ID)
{
  auto it = m.find(key);
  if (it != m.end())
  {
    HA_ID = it->second;
    return true;
  }
  return false;
}
void print_(vector<Point> &grb_points)
{
  for (int n = 0; n < grb_points.size(); n++)
  {
    cout << grb_points.at(n).t.get(GRB_StringAttr_VarName)
         << ":\t"
         << grb_points.at(n).t.get(GRB_DoubleAttr_X)
         << "\t\t"
         << grb_points.at(n).v.get(GRB_StringAttr_VarName)
         << ":\t"
         << grb_points.at(n).v.get(GRB_DoubleAttr_X)
         << "\t\t";
    try
    {
      cout << grb_points.at(n).chi.get(GRB_StringAttr_VarName)
           << ":\t";
      if (grb_points.at(n).chi.get(GRB_DoubleAttr_X) == 1)
        cout << 1 << "\t\t";
      else
        cout << 0 << "\t\t";
    }
    catch (GRBException &ex)
    {
      cout << "chi"
           << ":\t"
           << "---"
           << "\t\tw";
    }
    try
    {
      cout << grb_points.at(n).nu.get(GRB_StringAttr_VarName)
           << ":\t"
           << grb_points.at(n).nu.get(GRB_DoubleAttr_X)
           << "\t";
    }
    catch (GRBException &ex)
    {
      cout << "nu"
           << ":\t"
           << "---"
           << "\t";
    }
    cout << endl;
  }
}
