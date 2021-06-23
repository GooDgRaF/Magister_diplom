//
// Created by Антон on 14.04.2020.
//

#ifndef TIMES_AND_PLANES_CALCULATE_TIMES_H
#define TIMES_AND_PLANES_CALCULATE_TIMES_H

#include <Measure units/Time.h>
#include <Fields of Zone/Point.h>
#include "Zone.h"

void
calc_TimeSegments(Flow &flow, const std::vector<CheckPoint> &checkPoints,
                  const std::vector<WaitingArea> &waitingAreas, int start_point = -1, int end_point = -1);

void calc_TS_edges_of_constricted_zone(Zone &zone);

TS plane_arc_Time(const CheckPoint &start, const CheckPoint &second, const PlanePoint &plane);

TS semicircle_Time(const CheckPoint &start, const CheckPoint &second);

int topID(Flow &flow, const int point_ID);

#endif //TIMES_AND_PLANES_CALCULATE_TIMES_H
