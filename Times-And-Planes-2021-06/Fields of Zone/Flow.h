//
// Created by Антон on 23.03.2020.
//

#ifndef TIMES_AND_PLANES_FLOW_H
#define TIMES_AND_PLANES_FLOW_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include "Measure units/MeasureUnits.h"

struct Flow
{
    std::string name;
    int ID;
    int start_point;
    std::map<int, std::vector<int>> graph_of_descendants; //Подграф графа Zone, заданный списками Следующий
    std::map<int, std::vector<int>> graph_of_ancestors; //Подграф графа Zone, заданный списками Предшествующий
    std::set<int> points; //Множество точек принадлежащих потоку
    std::vector<int> path; //Массив вершин в исходных обозначениях в топологическом порядке
    std::map<int, std::vector<TS>> times; //Отображение ID точки --> временные интервалы {(Tmin_0, Tmax_0), (Tmin_1, Tmax_1), ...  } без пересечений
    std::map<int, std::vector<std::pair<TS, int>>> not_merged_times; //Отображение ID точки --> { ([t1,t2], parent) ... ([tn-1,tn], parent) }. У первой вершины предок -1

    void print_times();
};


#endif //TIMES_AND_PLANES_FLOW_H
