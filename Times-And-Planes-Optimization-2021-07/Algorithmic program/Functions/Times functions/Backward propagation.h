//
// Created by Антон on 21.06.2021.
//

#ifndef TIMES_AND_PLANES_2021_06_BACKWARD_PROPAGATION_H
#define TIMES_AND_PLANES_2021_06_BACKWARD_PROPAGATION_H

#include <Algorithmic program/Zone.h>

Trajectory backward_propagation(Zone &zone, int flow_ID, const Time &goal, int start_point = -1, int stop_backward_point = -1);


#endif //TIMES_AND_PLANES_2021_06_BACKWARD_PROPAGATION_H
