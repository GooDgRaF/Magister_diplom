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

void
calc_best_trajectory(std::vector<std::map<int, int>> &trjs, const int point_to_reach, const int current_point)
    {
        static std::map<int, int> trj{};
        if (current_point == point_to_reach)
        {
            //estimate trj
            trjs.push_back(trj);
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
