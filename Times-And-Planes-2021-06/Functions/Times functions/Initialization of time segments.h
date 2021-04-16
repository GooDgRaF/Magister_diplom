//
// Created by Антон on 21.01.2021.
//

#ifndef MAIN_CPP_INITIALIZATION_OF_TIME_SEGMENTS_H
#define MAIN_CPP_INITIALIZATION_OF_TIME_SEGMENTS_H

#include <Fields of Zone/Flow.h>
#include <Fields of Zone/Point.h>

void
initialTimes(Flow &flow, const std::vector<CheckPoint> &checkPoints, const PlanePoint &plane, const std::pair<int, int> &edge_ID_ID);

#endif //MAIN_CPP_INITIALIZATION_OF_TIME_SEGMENTS_H
