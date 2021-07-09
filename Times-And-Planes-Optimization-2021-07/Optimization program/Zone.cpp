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


