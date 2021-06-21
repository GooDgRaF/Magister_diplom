//
// Created by Антон on 21.06.2021.
//

#ifndef TIMES_AND_PLANES_2021_06_BACKWARD_PROPAGATION_H
#define TIMES_AND_PLANES_2021_06_BACKWARD_PROPAGATION_H

#include <Zone.h>

void backward_propagation(Zone &zone, int flow_ID, const TS &goal = Time::create_zero_TS(), int start_point = -1);

TS intersection_TS(const TS &ab, const TS &cd);

#endif //TIMES_AND_PLANES_2021_06_BACKWARD_PROPAGATION_H
