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

struct Point
{
    int ID;
    GRBVar t;
    GRBVar v;
    GRBVar S;
    GRBVar nu;
    GRBVar chi;
    
    static Point create_LPoint(GRBModel &model, int ID, const Point &pred, double S_edge)
    {
        Point p;
        p.ID = ID;
        
        string numS;
        i2s(ID, 2, numS);
        p.t = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "t" + numS);
        p.v = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "v" + numS);
        p.S = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "S" + numS);
        p.chi = model.addVar(0, 1, 1, GRB_BINARY, "chi" + numS);
        
        double v_min{zone.checkPoints.at(ID).V_min.meters_per_second};
        double v_max{zone.checkPoints.at(ID).V_max.meters_per_second};
        model.addConstr(v_min <= p.v);
        model.addConstr(v_max >= p.v);
        
        model.addConstr(p.S == S_edge);
        
        model.addQConstr((1 - p.chi)*pred.v + p.chi*v_min, GRB_LESS_EQUAL, p.v);
        model.addQConstr((1 - p.chi)*pred.v + p.chi*v_max, GRB_GREATER_EQUAL, p.v);
        model.addQConstr(2*p.S, GRB_EQUAL, (p.v + pred.v)*(p.t - pred.t));
        
        
        return p;
    }
    static Point create_HAPoint(GRBModel &model, int ID, const double t_min, const double t_max)
    {
        Point p;
        p.ID = ID;
        
        string numS;
        i2s(ID, 2, numS);
        p.t = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "t" + numS);
        p.v = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "v" + numS);
        p.nu = model.addVar(0, 1, 1, GRB_BINARY, "nu" + numS);
        
        double v_min{zone.checkPoints.at(ID).V_min.meters_per_second};
        double v_max{zone.checkPoints.at(ID).V_max.meters_per_second};
        model.addConstr(v_min <= p.v);
        model.addConstr(v_max >= p.v);
        
        model.addConstr(t_min <= p.t);
        model.addConstr(t_max >= p.t);
        
        
        return p;
    };
};

void print_(vector<Point> &grb_points)
{
    for (int n = 1; n < grb_points.size(); n++)
    {
        cout //<< setw(4)
                << grb_points.at(n).t.get(GRB_StringAttr_VarName)
                << ":  "
                << grb_points.at(n).t.get(GRB_DoubleAttr_X)
                << "\t"
                << grb_points.at(n).chi.get(GRB_StringAttr_VarName)
                << ":  "
                << grb_points.at(n).chi.get(GRB_DoubleAttr_X)
                << "\t"
                << grb_points.at(n).v.get(GRB_StringAttr_VarName)
                << ":  "
                << grb_points.at(n).v.get(GRB_DoubleAttr_X)
                << endl;
    }
}
bool isBetter(const std::map<int, int> &trj, int start_point, int end_point, double t0, double v0, double tEnd)
{
    GRBEnv *env = new GRBEnv();
    GRBModel model = GRBModel(*env);
    
    Point grb_start_point;
    grb_start_point.t = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "t0");
    grb_start_point.v = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "v0");
    
    model.addConstr(grb_start_point.t == t0); //s
    model.addConstr(grb_start_point.v == v0); //m/s
    
    
    vector<Point> grb_points{grb_start_point};
    int i{start_point};
    do //TODO Включить ЗО в рассчёты
    {
        CheckPoint pred = zone.checkPoints.at(i);
        i = trj.at(i);
        CheckPoint current = zone.checkPoints.at(i);
        grb_points.push_back(Point::create_LPoint(model, i, grb_points.back(), distance(pred, current).m()));//m
    }
    while (i != end_point);
    
    model.addConstr(grb_points.back().t == tEnd);
    
    model.set(GRB_IntParam_Threads, 6);
    model.set(GRB_IntParam_NonConvex, 2);
    model.optimize();
    
    
    print_(grb_points);
    
    
    return true;
}
