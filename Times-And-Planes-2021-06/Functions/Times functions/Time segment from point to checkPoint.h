//
// Created by Антон on 21.01.2021.
//

#ifndef MAIN_CPP_TIME_SEGMENT_FROM_POINT_TO_CHECKPOINT_H
#define MAIN_CPP_TIME_SEGMENT_FROM_POINT_TO_CHECKPOINT_H

#include <Measure units/Time.h>
#include <Fields of Zone/Point.h>

TS plane_checkPoint_Time(const PlanePoint &plane, const CheckPoint &point_there);

TS checkPoint_checkPoint_Time(const CheckPoint &point_from, const CheckPoint &point_there);


#endif //MAIN_CPP_TIME_SEGMENT_FROM_POINT_TO_CHECKPOINT_H
