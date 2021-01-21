//
// Created by Антон on 14.04.2020.
//

#ifndef TIMES_AND_PLANES_CALCULATE_TIMES_H
#define TIMES_AND_PLANES_CALCULATE_TIMES_H

#include "Zone.h"

void
calculateTimes(Flow &flow, const vector<CheckPoint> &checkPoints, const vector<StandardScheme> &standardSchemes, int i = -1);
#endif //TIMES_AND_PLANES_CALCULATE_TIMES_H
