//
// Created by Антон on 21.01.2021.
//

#ifndef MAIN_CPP_ARC_TIME_H
#define MAIN_CPP_ARC_TIME_H


#include <Measure units/Time.h>
#include <Fields of Zone/Point.h>

TS plane_arc_Time(const CheckPoint &start, const CheckPoint &second, const PlanePoint &plane);

TS semicircle_Time(const CheckPoint &start, const CheckPoint &second);


#endif //MAIN_CPP_ARC_TIME_H
