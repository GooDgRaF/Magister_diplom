//
// Created by Антон on 21.06.2021.
//

#ifndef TIMES_AND_PLANES_2021_06_BACKWARD_PROPAGATION_H
#define TIMES_AND_PLANES_2021_06_BACKWARD_PROPAGATION_H

#include <Zone.h>

void backward_propagation(Zone &zone, int flow_ID, const TS &goal = {0,0}, int start_point = -1);


#endif //TIMES_AND_PLANES_2021_06_BACKWARD_PROPAGATION_H
