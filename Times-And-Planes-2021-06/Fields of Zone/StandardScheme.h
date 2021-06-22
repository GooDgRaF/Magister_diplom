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
    int end_ID; //ID точки начала прямого движения к стартовой точке

    int repeat; //Количество повторений стандартной схемы

    CheckPoint start;//
    CheckPoint second;// Точки стандартной схемы
    CheckPoint third;//
    CheckPoint end; //

    Distance first_semicircle_length = Distance::createM(0);//Длина дуги первой полуокружности
    TS first_semicircle_T{0,0};//Временной интервал, описывающий прохождение по первой полуокружности
    Distance line_back = Distance::createM(0);//Длина обратного плеча
    TS line_back_T{0,0};//Временной интервал, описывающий прохождение обратного плеча

    Distance second_semicircle_length = Distance::createM(0);//Длина дуги первой полуокружности
    TS second_semicircle_T{0,0};//Временной интервал, описывающий прохождение по первой полуокружности
    Distance line_forward = Distance::createM(0);//Длина обратного плеча
    TS line_forward_T{0,0};//Временной интервал, описывающий прохождение обратного плеча


    Time Tmin = Time::createTsec(0); //Минимальное время прохода по стандартной схеме
    Time Tmax = Time::createTsec(0); //Максимальное время прохода по стандартной схеме
    TS min_max_time{0, 0};

};


#endif //TIMES_AND_PLANES_STANDARDSCHEME_H
