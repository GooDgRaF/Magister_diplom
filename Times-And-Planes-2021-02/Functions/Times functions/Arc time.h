//
// Created by Антон on 21.01.2021.
//

#ifndef MAIN_CPP_ARC_TIME_H
#define MAIN_CPP_ARC_TIME_H


#include <Measure units/Time.h>
#include <Fields of Zone/Point.h>

std::pair<Time, Time> plane_arc_Time(const CheckPoint &start, const CheckPoint &second, const PlanePoint &plane);

std::pair<Time, Time> semicircle_Time(const CheckPoint &start, const CheckPoint &second);


#endif //MAIN_CPP_ARC_TIME_H
