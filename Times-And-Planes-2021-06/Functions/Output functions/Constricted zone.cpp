//
// Created by Антон on 18.06.2021.
//

#include <fstream>
#include "Constricted zone.h"
#include "iostream"

using namespace std;

void out_constricted_zone(const Zone &zone)
    {
        ofstream out("Constricted zone.txt");
        
        out << "@PointsQnt" << endl;
        out << zone.constricted_graph.size() << endl;
        
        out << "@Points" << endl;
        {
            string route = "route";
            for (const auto &item : zone.constricted_graph)
            {
                out << zone.checkPoints[item.first].name << " " << route << endl;
            }
        }
        
        out << "@FinalPoint" << endl;
        out << zone.checkPoints[find_final_point_in_constricted_zone(zone.constricted_graph)].name << endl;
        
        out << "@FlowsQnt" << endl;
        out << zone.flows.size() << endl;
        
        out << "@FlowsInfo" << endl;
        set<size_t> start_points{};
        for (const auto &item : zone.flows)
        {
            start_points.insert(item.start_point);
        }
        auto safety_interval = " 180 ", flow_type = "-1 ";
        for (const auto &edge_ts : zone.edge_ts)
        {
            if (start_points.find(edge_ts.first.from) != start_points.end())
            {
                double t_min = edge_ts.second.min.get_sec(1), t_max = edge_ts.second.max.get_sec(1);
                out << zone.checkPoints[edge_ts.first.there].name << safety_interval << flow_type <<
                    t_min << " " << round((1.0/3*t_min + 2.0/3*t_max)) << " " << t_max << endl;
            }
        }
        
        out << "@RouteStructure" << endl;
        for (const auto &edge_ts : zone.edge_ts)
        {
            bool is_start_point{false};
            for (const auto &flow : zone.flows)
            {
                if (edge_ts.first.from == flow.start_point)
                {
                    is_start_point = true;
                    break;
                }
            }
            if (!is_start_point)
            {
                double t_min = edge_ts.second.min.get_sec(1), t_max = edge_ts.second.max.get_sec(1);
                out << zone.checkPoints[edge_ts.first.from].name << " " <<
                    zone.checkPoints[edge_ts.first.there].name << " " <<
                    t_min << " " << round((1.0/3*t_min + 2.0/3*t_max)) << " " << t_max << endl;
            }
        }
    }

int find_final_point_in_constricted_zone(const map<int, vector<int>> &constricted_zone)
    {
        set<int> ancestors_in_constr_zone{};
        set<int> sons_in_constr_zone{};
        for (const auto &item : constricted_zone)
        {
            for (const auto &ancestor : item.second)
            {
                ancestors_in_constr_zone.insert(ancestor);
            }
            sons_in_constr_zone.insert(item.first);
        }
        for (const auto &son : sons_in_constr_zone)//Ищем точку которая не является родителем никакой другой точки
        {
            if (ancestors_in_constr_zone.find(son) == ancestors_in_constr_zone.end())
                return son;
        }
        return -1;
    }