//
// Created by Антон on 10.02.2020.
//

#ifndef TIMES_AND_PLANES_CHECKPOINT_H
#define TIMES_AND_PLANES_CHECKPOINT_H

#include <string>
#include <vector>
#include "Measure units/MeasureUnits.h"

struct Point
{
    Coordinate x = Coordinate::createMs(0);
    Coordinate y = Coordinate::createMs(0);
    Coordinate z = Coordinate::createMs(0);

    Coordinate sq_abs() const
        {
            return x * x + y * y + z * z;
        }
};



struct CheckPoint : Point
{
    std::string name;
    Velocity Vmin = Velocity::createVkm_h(0);
    Velocity Vmax = Velocity::createVkm_h(0);
    bool landing_flag = false;
};


struct PlanePoint : Point
{
    Velocity V = Velocity::createVkm_h(0);
};


#endif //TIMES_AND_PLANES_CHECKPOINT_H
