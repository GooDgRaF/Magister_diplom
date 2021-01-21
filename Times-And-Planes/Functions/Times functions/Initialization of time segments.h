//
// Created by Антон on 21.01.2021.
//

#ifndef MAIN_CPP_INITIALIZATION_OF_TIME_SEGMENTS_H
#define MAIN_CPP_INITIALIZATION_OF_TIME_SEGMENTS_H

#include <Fields of Zone/Flow.h>
#include <Fields of Zone/Point.h>

void initialTimes(Flow &flow, const vector<CheckPoint> &checkPoints,
                  const PlanePoint &plane, const pair<int, int> &edge_ID_ID, const int ID_there);

#endif //MAIN_CPP_INITIALIZATION_OF_TIME_SEGMENTS_H
