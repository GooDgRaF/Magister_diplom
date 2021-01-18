//
// Created by Антон on 18.01.2021.
//

#include "Fill checkPoint coordinate and velocity.h"

enum MeasureUnits_Coordinate
{
    meters = 109, //m
    kilometers = 216, //km
    naval_miles = 155, //NM
};

enum MeasureUnits_Velocity
{
    meters_per_second = 319, //m_s
    kilometers_per_hour = 415, //km_h
    naval_miles_per_hour = 354 //NM_h
};


void fill_checkPoint_coordinate(Coordinate &coordinate_field, const int measure_unit, const double value)
    {
        switch (measure_unit)
        {
            case meters: coordinate_field = Coordinate::createMs(value);
                break;
            case kilometers: coordinate_field = Coordinate::createKms(value);
                break;
            case naval_miles: coordinate_field = Coordinate::createNMs(value);
                break;
            default: std::cerr << "Error! Wrong unit of coordinate measurement." << std::endl;
                exit(-3);
        }


    }

void fill_checkPoint_velocity(Velocity &velocity_field, const int measure_unit, const double value)
    {
        switch (measure_unit)
        {
            case meters_per_second: velocity_field = Velocity::createVm_s(value);
                break;
            case kilometers_per_hour: velocity_field = Velocity::createVkm_h(value);
                break;
            case naval_miles_per_hour: velocity_field = Velocity::createVNM_h(value);
                break;

            default: std::cerr << "Error! Wrong unit of velocity measurement." << std::endl;
                exit(-3);
        }

    }
