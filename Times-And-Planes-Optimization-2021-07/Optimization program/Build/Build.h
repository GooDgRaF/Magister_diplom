//
// Created by Антон on 09.07.2021.
//

#ifndef TIMES_AND_PLANES_OPTIMIZATION_2021_07_BUILD_H
#define TIMES_AND_PLANES_OPTIMIZATION_2021_07_BUILD_H
#include "string_view"

void fill_Zone(std::string_view path_PointsFile, std::string_view path_HoldingAreas, std::string_view path_SchemesFile);

void build_graph_of_Zone();
#endif //TIMES_AND_PLANES_OPTIMIZATION_2021_07_BUILD_H
