//
// Created by Антон on 07.07.2021.
//

#ifndef TIMES_AND_PLANES_OPTIMIZATION_2021_07_1_H
#define TIMES_AND_PLANES_OPTIMIZATION_2021_07_1_H

#include <string>
#include <vector>

struct Point
{
    Distance x = Distance::createM(0);
    Distance y = Distance::createM(0);
    Distance z = Distance::createM(0);
    
//    Distance sq_abs() const
//        {
//            return x * x + y * y + z * z;
//        }
};



struct CheckPoint : Point
{
    int ID;
    std::string name;
    Velocity Vmin = Velocity::createVkm_h(0);
    Velocity Vmax = Velocity::createVkm_h(0);
    bool landing_flag = false;
};
#endif //TIMES_AND_PLANES_OPTIMIZATION_2021_07_1_H
