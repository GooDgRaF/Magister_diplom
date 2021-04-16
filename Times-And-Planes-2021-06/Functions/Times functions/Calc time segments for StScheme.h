//
// Created by Антон on 23.01.2021.
//

#ifndef MAIN_CPP_CALC_TIME_SEGMENTS_FOR_STSCHEME_H
#define MAIN_CPP_CALC_TIME_SEGMENTS_FOR_STSCHEME_H

#include <Fields of Zone/Flow.h>
#include <Fields of Zone/Point.h>

void
calc_and_initStScheme(Flow &flow, const std::vector<CheckPoint> &checkPoints, const PlanePoint &plane, const std::pair<int, int> &edge_ID_ID, int &there_ID);

#endif //MAIN_CPP_CALC_TIME_SEGMENTS_FOR_STSCHEME_H
