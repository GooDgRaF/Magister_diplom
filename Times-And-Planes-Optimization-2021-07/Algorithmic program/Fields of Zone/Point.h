//
// Created by Антон on 10.02.2020.
//

#ifndef TIMES_AND_PLANES_CHECKPOINT_H
#define TIMES_AND_PLANES_CHECKPOINT_H

#include <string>
#include <vector>
#include "Algorithmic program/Measure units/MeasureUnits.h"

struct Point
{
    Distance x = Distance::createM(0);
    Distance y = Distance::createM(0);
    Distance z = Distance::createM(0);

    Distance sq_abs() const
        {
            return x * x + y * y + z * z;
        }
};



struct CheckPoint : Point
{
    int ID;
    std::string name;
    Velocity Vmin = Velocity::createVkm_h(0);
    Velocity Vmax = Velocity::createVkm_h(0);
    bool landing_flag = false;
};


struct PlanePoint : Point
{
    Velocity V = Velocity::createVkm_h(0);
    std::string flow_for_plane;
    std::string destination;
    std::pair<std::string,std::string> on_edge;
};


#endif //TIMES_AND_PLANES_CHECKPOINT_H
