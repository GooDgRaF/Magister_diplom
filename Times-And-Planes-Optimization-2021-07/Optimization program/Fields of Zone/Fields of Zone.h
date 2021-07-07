//
// Created by Антон on 07.07.2021.
//

#ifndef TIMES_AND_PLANES_OPTIMIZATION_2021_07_FIELDS_OF_ZONE_H
#define TIMES_AND_PLANES_OPTIMIZATION_2021_07_FIELDS_OF_ZONE_H

#include <string>
#include <vector>
#include "Optimization program/Measure units/Measure units.h"

struct CheckPoint
{
    int ID{0};
    std::string name{};
    Distance x{0};
    Distance y{0};
    Distance z{0};
    Velocity Vmin{0};
    Velocity Vmax{0};
    bool landing_flag = false;
};


#endif //TIMES_AND_PLANES_OPTIMIZATION_2021_07_FIELDS_OF_ZONE_H
