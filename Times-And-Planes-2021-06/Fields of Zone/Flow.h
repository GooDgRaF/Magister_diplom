//
// Created by Антон on 23.03.2020.
//

#ifndef TIMES_AND_PLANES_FLOW_H
#define TIMES_AND_PLANES_FLOW_H

#include <vector>
#include <string>
#include <map>
#include "Measure units/MeasureUnits.h"

struct Flow
{
    std::string name;
    int start_point;
    std::map<int, std::vector<int>> graph_of_descendants; //Подграф графа Zone, заданный списками Следующий
    std::map<int, std::vector<int>> graph_of_ancestors; //Подграф графа Zone, заданный списками Предшествующий
    std::vector<int> keys; //Массив для значений вершин после топологической сортировки
    std::map<int, std::vector<std::pair<Time, Time>>> times; //Отображение ID точки --> временные интервалы (Tmin, Tmax) без пересечений
    std::map<int, std::vector<std::pair<Time, Time>>> not_merged_times; //Отображение ID точки --> временные интервалы (Tmin, Tmax) возможно с пересечением

    void print_times();
};


#endif //TIMES_AND_PLANES_FLOW_H
