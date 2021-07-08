//
// Created by Антон on 07.07.2021.
//

#ifndef TIMES_AND_PLANES_OPTIMIZATION_2021_07_FIELDS_OF_ZONE_H
#define TIMES_AND_PLANES_OPTIMIZATION_2021_07_FIELDS_OF_ZONE_H

#include <string>
#include <vector>
#include <set>
#include "Optimization program/Measure units/Measure units.h"

struct CheckPoint
{
    int ID{-1};
    std::string name{};
    Coordinate x{0};
    Coordinate y{0};
    Coordinate z{0};
    Velocity Vmin{0};
    Velocity Vmax{0};
    bool landing_flag = false;
    
    std::set<int> schemes_start{};//?
};

struct Scheme
{
    int start{};
    int ID{-1};
    std::vector<int> path{};// Номинальный путь
    
    std::string type{"N"}; //Тип спрямления: N - нет спрямления, F - веер, T - полутромбон, O - внешнее, B - конечная(ые) точки спрямления принадлежат схеме
    std::vector<int> straighteningFrom{};
    std::vector<int> straighteningTo{};
};


#endif //TIMES_AND_PLANES_OPTIMIZATION_2021_07_FIELDS_OF_ZONE_H
