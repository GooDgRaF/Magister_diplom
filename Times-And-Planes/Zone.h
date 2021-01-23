//
// Created by Антон on 27.03.2020.
//

#ifndef TIMES_AND_PLANES_ZONE_H
#define TIMES_AND_PLANES_ZONE_H

#include <vector>
#include <algorithm>
#include <Fields of Zone/StandardScheme.h>
#include "Fields of Zone/Point.h"
#include "Fields of Zone/Scheme.h"
#include "Fields of Zone/Flow.h"
#include "Measure units/MeasureUnits.h"

struct Zone
{
    std::vector<std::vector<int>> graph_of_descendants; //Граф зоны задан списками Следующий
    std::vector<CheckPoint> checkPoints;
    std::vector<Scheme> schemes;
    std::vector<Flow> flows;
    std::vector<StandardScheme> standardSchemes;
	
	void print_flows_keys();
	
	void print_key_of_flow(int number_of_flow);
	
	void print_as_string();
	
	void print_flows_as_string_des();
	
	void print_flows_as_string_anc();
	
	void print_flows_as_string_des(bool sort);
	
	void print_times();

	void print_not_merged_times();
};


#endif //TIMES_AND_PLANES_ZONE_H
