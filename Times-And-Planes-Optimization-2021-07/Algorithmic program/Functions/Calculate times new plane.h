//
// Created by Антон on 14.01.2021.
//

#ifndef MAIN_CPP_CALCULATE_TIMES_NEW_PLANE_H
#define MAIN_CPP_CALCULATE_TIMES_NEW_PLANE_H

#include <Algorithmic program/Zone.h>

void calc_plane(Zone &zone, const PlanePoint &plane,
                std::map<int, std::vector<std::pair<double, double>>> &result,
                std::map<int, std::vector<std::pair<std::pair<double, double>, int>>> &not_merged_result,
                const std::vector<int> &ID_points_to_calculate = {});

#endif //MAIN_CPP_CALCULATE_TIMES_NEW_PLANE_H
