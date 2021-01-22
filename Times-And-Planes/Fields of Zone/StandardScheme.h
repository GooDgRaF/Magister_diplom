//
// Created by Антон on 05.05.2020.
//

#ifndef TIMES_AND_PLANES_STANDARDSCHEME_H
#define TIMES_AND_PLANES_STANDARDSCHEME_H


#include <string>
#include <vector>
#include <Measure units/Time.h>
#include "Point.h"


struct StandardScheme
{
    std::string name;

    int start_ID; //ID точки начала и конца стандартной схемы
    int second_ID; //ID точки начала обратного плеча стандартной схемы
    int third_ID; //ID точки конца обратного плеча стандартной схемы

    int repeat; //Количество повторений стандартной схемы

    CheckPoint start;//
    CheckPoint second;// Точки стандартной схемы
    CheckPoint third;//
    CheckPoint end; //

    Distance semicircle_length = Distance::createMs(0);//Длина дуги полуокружности
    std::pair<Time,Time> semicircle_T = {Time::createTsec(0),Time::createTsec(0)};//Временной интервал, описывающий прохождение полуокружности

    Distance line = Distance::createMs(0);//Длина обратного плеча
    std::pair<Time,Time> line_T = {Time::createTsec(0),Time::createTsec(0)};//Временной интервал, описывающий прохождение обратного плеча

    Time Tmin = Time::createTsec(0); //Минимальное время прохода по стандартной схеме
    Time Tmax = Time::createTsec(0); //Максимальное время прохода по стандартной схеме

};


#endif //TIMES_AND_PLANES_STANDARDSCHEME_H
