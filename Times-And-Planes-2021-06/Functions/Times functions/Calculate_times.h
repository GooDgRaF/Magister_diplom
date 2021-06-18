//
// Created by Антон on 14.04.2020.
//

#ifndef TIMES_AND_PLANES_CALCULATE_TIMES_H
#define TIMES_AND_PLANES_CALCULATE_TIMES_H

#include "Zone.h"

int topID(Flow &flow, const int point_ID);

void
calc_TimeSegments(Flow &flow, const std::vector<CheckPoint> &checkPoints,
                  const std::vector<StandardScheme> &standardSchemes, int start_point = -1, int end_point = -1);

#endif //TIMES_AND_PLANES_CALCULATE_TIMES_H
