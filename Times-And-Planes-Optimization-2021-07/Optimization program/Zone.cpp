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

void calc_best_trajectory(std::vector<std::map<int, int>> &trjs, const int point_to_reach, const int current_point)
{
    static std::map<int, int> trj{};
    if (current_point == point_to_reach)
    {
        //estimate trj
        trjs.push_back(trj);
        
        if (isBetter(trj, 0, 0, 0, 0))
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
    GRBVar t;
    GRBVar v;
    GRBVar S;
    GRBVar nu;
    GRBVar chi;
    
    Point create_LPoint(GRBModel &model, int num, double t, double S_edge)
    {
        Point p;
        string numS;
        i2s(num, 2, numS);
        
        p.t = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "t" + numS);
        p.v = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "v" + numS);
        p.S = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "S" + numS);
        p.chi = model.addVar(0, 1, 0, GRB_BINARY, "chi" + numS);
        
        model.addConstr(S == S_edge);
        //TODO Линейный участок
        model.addConstr(v >= zone.checkPoints.at(num).Vmin.meters_per_second);
        model.addConstr(v <= zone.checkPoints.at(num).Vmax.meters_per_second);
        
        return p;
    }
};

bool isBetter(const std::map<int, int> &trj, int start_point, double t0, double v0, double tEnd)
{
    GRBEnv *env = new GRBEnv();
    GRBModel model = GRBModel(env);
    
    GRBVar grb_t0 = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "t0");
    GRBVar grb_v0 = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "v0");
    GRBVar grb_tEnd = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "tEnd");
    
    model.addConstr(grb_t0 == t0);
    model.addConstr(grb_v0 == v0);
    model.addConstr(grb_tEnd == tEnd);
    
    
    for (int i = trj.at(start_point); i < trj.size(); i = trj.at(i))
    {
    }
}
