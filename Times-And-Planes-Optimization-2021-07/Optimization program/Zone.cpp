//
// Created by Антон on 07.07.2021.
//
#include <iostream>

#include "Zone.h"

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

std::map<int, int> calc_best_trajectory(std::map<int, int> &trj, const int stop_point, const int current_point)
    {
        if (current_point == stop_point)
            return trj;
        else
        {
            for (const auto parent : zone.ancestors_graph.at(current_point))
            {
                trj.insert({parent, current_point});
                auto trj_to_estimate = calc_best_trajectory(trj,stop_point, parent);
                //estimate_Trajectory(trj_to_estimate);
                zone.trj = trj_to_estimate;
                zone.trjs.push_back(trj_to_estimate);
                //zone.trjs.push_back(trj); //Все возможные пути
                trj.erase(parent);
            }
            return trj;
        }
    }
