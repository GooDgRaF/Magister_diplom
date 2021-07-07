//
// Created by Антон on 07.07.2021.
//
#include "Measure units.h"

Distance operator+(const Distance &l_d, const Distance &r_d)
    {
        return {l_d.meter + r_d.meter, "m"};
    }

Distance operator-(const Distance &l_d, const Distance &r_d)
    {
        return {l_d.meter - r_d.meter, "m"};
    }