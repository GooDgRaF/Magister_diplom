//
// Created by Антон on 07.07.2021.
//

#ifndef TIMES_AND_PLANES_OPTIMIZATION_2021_07_FIELDS_OF_FLOW_H
#define TIMES_AND_PLANES_OPTIMIZATION_2021_07_FIELDS_OF_FLOW_H

#include <string>
#include <vector>
#include <set>
#include "Optimization program/Measure units/Measure units.h"
#include "cmath"

struct CheckPoint
{
    int ID{-1};
    std::string name{};
    Coordinate x{0};
    Coordinate y{0};
    Coordinate z{0};
    Velocity V_min{0};
    Velocity V_max{0};
    bool landing_flag = false;
    
    std::vector<int> vs; //vs - vertexs  связанные с данной контрольной точкой вершины
};
Coordinate distance(const CheckPoint &a, const CheckPoint &b);

struct Scheme
{
    int ID{-1};
    std::vector<int> path{};//Полный путь по схеме
    
    std::string type{"N"}; //Тип спрямления: N - нет спрямления, F - веер, T - полутромбон, S - спрямление
    std::vector<int> stFrom{}; // st - straightening
    std::vector<int> stTo{};
};

struct HoldingArea
{
    int ID{-1};
    Time t_min{0};
    Time t_max{0};
};


#endif //TIMES_AND_PLANES_OPTIMIZATION_2021_07_FIELDS_OF_FLOW_H
