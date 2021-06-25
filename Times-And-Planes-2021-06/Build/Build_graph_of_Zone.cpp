//
// Created by Антон on 23.03.2020.
//

#include <iostream>
#include <Functions/Geometric functions/Calculate standard scheme.h>
#include "Build_graph_of_Zone.h"

using namespace std;

void Build_graph_of_Zone(Zone &zone)
    {
        for (const auto &scheme : zone.schemes) //Строим граф списками Следующий
        {
            assert(!scheme.path.empty()); //Пустая схема --- см как считываешь схемы!
            for (int i = 0; i < scheme.path.size() - 1; i++)
            {
                zone.graph[scheme.path[i]].push_back(scheme.path[i + 1]); //Соединить текущую точку со следующей
            }
        }
    }