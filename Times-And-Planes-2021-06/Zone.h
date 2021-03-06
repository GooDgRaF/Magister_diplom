//
// Created by Антон on 27.03.2020.
//

#ifndef TIMES_AND_PLANES_ZONE_H
#define TIMES_AND_PLANES_ZONE_H

#include <vector>
#include <set>
#include <algorithm>
#include <Fields of Zone/StandardScheme.h>
#include "Fields of Zone/Point.h"
#include "Fields of Zone/Scheme.h"
#include "Fields of Zone/Flow.h"
#include "Measure units/MeasureUnits.h"

using TS = std::pair<Time, Time>; //TS - time segments - временные интервалы
using edge = std::pair<int, int>; //Ребро графа

struct Zone
{
    std::vector<std::vector<int>> graph; //Граф зоны. Задан списками Следующий
    std::map<int, std::vector<int>> constricted_graph; //Сжатый граф зоны. Задан списками предшественников
    std::map<edge, TS> constricted_ts; //Ребро из constricted_graph_of_parents --> временнЫе интервалы
    std::vector<CheckPoint> checkPoints;
    std::vector<Scheme> schemes;
    std::vector<Flow> flows;
    std::vector<StandardScheme> standardSchemes;
    
    int final_point{-1};
	
	void print_flows_keys();
	
	void print_key_of_flow(int number_of_flow);
	
	void print_as_string();
	
	void print_flows_as_string_des();
	
	void print_flows_as_string_anc();
	
	void print_flows_as_string_des(bool sort);
	
	void print_times();

	void print_not_merged_times();
	
	void print_constricted_graph_of_parents();
	
	void print_constricted_TS();
};


#endif //TIMES_AND_PLANES_ZONE_H
