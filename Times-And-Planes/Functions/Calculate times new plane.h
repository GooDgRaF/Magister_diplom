//
// Created by Антон on 14.01.2021.
//

#ifndef MAIN_CPP_CALCULATE_TIMES_NEW_PLANE_H
#define MAIN_CPP_CALCULATE_TIMES_NEW_PLANE_H

#include <Zone.h>

std::map<int, std::vector<std::pair<double, double>>>
calc_plane(Zone &zone, const PlanePoint &plane, const std::vector<int> &ID_points_to_calculate = {});

#endif //MAIN_CPP_CALCULATE_TIMES_NEW_PLANE_H
