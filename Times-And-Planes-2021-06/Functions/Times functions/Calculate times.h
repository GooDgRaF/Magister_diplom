//
// Created by Антон on 14.04.2020.
//

#ifndef TIMES_AND_PLANES_CALCULATE_TIMES_H
#define TIMES_AND_PLANES_CALCULATE_TIMES_H

#include "Zone.h"

void
calc_ts(Flow &flow,
        const std::vector<CheckPoint> &checkPoints,
        const std::vector<StandardScheme> &standardSchemes, int i = -1);

#endif //TIMES_AND_PLANES_CALCULATE_TIMES_H
