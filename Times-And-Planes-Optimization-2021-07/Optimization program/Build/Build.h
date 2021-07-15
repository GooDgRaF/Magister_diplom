//
// Created by Антон on 09.07.2021.
//

#ifndef TIMES_AND_PLANES_OPTIMIZATION_2021_07_BUILD_H
#define TIMES_AND_PLANES_OPTIMIZATION_2021_07_BUILD_H

#include "string_view"

void build_Flow(std::string_view path_PointsFile, std::string_view path_HoldingAreas, std::string_view path_SchemesFile);

void build_hull_of_Flow();
void build_graph_of_Flow(int start_point);

#endif //TIMES_AND_PLANES_OPTIMIZATION_2021_07_BUILD_H
