//
// Created by Антон on 05.05.2020.
//

#ifndef TIMES_AND_PLANES_STANDARDSCHEME_H
#define TIMES_AND_PLANES_STANDARDSCHEME_H


#include <string>
#include <vector>
#include <Measure units/Time.h>
#include "Point.h"

using namespace std;

struct StandardScheme
{
    string name;
    int start_ID; //ID точки начала и конца стандартной схемы
    int second_ID; //ID точки начала обратного плеча стандартной схемы
    int third_ID; //ID точки конца обратного плеча стандартной схемы
    int repeat; //Количество повторений стандартной схемы
    CheckPoint start;//
    CheckPoint second;// Точки стандартной схемы
    CheckPoint third;//
    Time Tmin = Time::createTsec(0); //Минимальное время прохода по стандартной схеме
    Time Tmax = Time::createTsec(0); //Максимальное время прохода по стандартной схеме
};


#endif //TIMES_AND_PLANES_STANDARDSCHEME_H
