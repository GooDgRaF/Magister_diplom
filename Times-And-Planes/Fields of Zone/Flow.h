//
// Created by Антон on 23.03.2020.
//

#ifndef TIMES_AND_PLANES_FLOW_H
#define TIMES_AND_PLANES_FLOW_H

#include <vector>
#include <string>
#include <map>
#include "Measure units/MeasureUnits.h"

using namespace std;

struct Flow
{
	string name;
	int start_point;
	map<int, vector<int>> graph_of_descendants; //Подграф графа Zone, заданный списками Следующий
	map<int, vector<int>> graph_of_ancestors; //Подграф графа Zone, заданный списками Предшествующий
	vector<int> keys; //Массив для значений вершин после топологической сортировки
	map<int, vector<pair<Time, Time>>> times; //Отображение ID точки --> временные интервалы (Tmin, Tmax) без пересечений
    map<int, vector<pair<Time, Time>>> not_merged_times; //Отображение ID точки --> временные интервалы (Tmin, Tmax) возможно с пересечением
};


#endif //TIMES_AND_PLANES_FLOW_H
