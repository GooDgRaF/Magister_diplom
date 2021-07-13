//
// Created by Антон on 18.06.2021.
//

#include <fstream>
#include "Constricted zone.h"
#include "iostream"

using namespace std;

void out_constricted_zone(const Zone &zone) //TODO Согласовать с Арсением формат вывода несвязных множеств
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
        for (const auto &[edge, tss] : zone.edge_tss)
        {
            if (start_points.find(edge.from) != start_points.end())
            {
                double t_min = tss.front().min.get_sec(1), t_max = tss.back().max.get_sec(1);
                out << zone.checkPoints[edge.there].name << safety_interval << flow_type <<
                    t_min << " " << round((0.73*t_min + 0.27*t_max)) << " " << t_max << endl;
            }
        }
        
        out << "@RouteStructure" << endl;
        for (const auto &[edge, tss] : zone.edge_tss)
        {
            bool is_start_point{false};
            for (const auto &flow : zone.flows)
            {
                if (edge.from == flow.start_point)
                {
                    is_start_point = true;
                    break;
                }
            }
            if (!is_start_point)
            {
                double t_min = tss.front().min.get_sec(1), t_max = tss.back().max.get_sec(1);
                out << zone.checkPoints[edge.from].name << " " <<
                    zone.checkPoints[edge.there].name << " " <<
                    t_min << " " << round((0.73*t_min + 0.27*t_max)) << " " << t_max << endl;
            }
        }
    }

int find_final_point_in_constricted_zone(const map<int, vector<int>> &constricted_zone)
    {
        set<int> ancestors_in_constr_zone{};
        set<int> sons_in_constr_zone{};
        for (const auto &[son, ancestors] : constricted_zone)
        {
            for (const auto &ancestor : ancestors)
                ancestors_in_constr_zone.insert(ancestor);
            
            sons_in_constr_zone.insert(son);
        }
        for (const auto &son : sons_in_constr_zone)//Ищем точку которая не является родителем никакой другой точки
        {
            if (ancestors_in_constr_zone.find(son) == ancestors_in_constr_zone.end())
                return son;
        }
        return -1;
    }