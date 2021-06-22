//
// Created by Антон on 21.04.2020.
//

#ifndef TIMES_AND_PLANES_MEASUREUNITS_H
#define TIMES_AND_PLANES_MEASUREUNITS_H

#include <cmath>
#include "Distance.h"
#include "Time.h"
#include "Velocity.h"

Velocity operator/(const Distance &x, const Time &t); //Перегрузка операторов

Velocity operator+(const Velocity &v, const Velocity &w);

Velocity operator-(const Velocity &v, const Velocity &w);

Velocity operator*(const double &a, const Velocity &v);

Velocity operator*(const Velocity &v, const double &a);

Time operator/(const Distance &x, const Velocity &v);

Time operator+(const Time &t0, const Time &t1);

Time operator-(const Time &t0, const Time &t1);

Time operator*(const double &a, const Time &t);

Time operator*(const Time &t, const double &a);

Distance operator+(const Distance &a, const Distance &b);

Distance operator-(const Distance &a, const Distance &b);

Distance operator*(const Time &t, const Velocity &v);

Distance operator*(const Velocity &v, const Time &t);

Distance operator*(const double &a, const Distance &x);

Distance operator*(const Distance &x, const double &a);

Distance operator*(const Distance &x, const Distance &y);

Distance operator/(const Distance &x, const Distance &y);

Distance pow(Distance x, int a);

Distance sqrt(Distance x);


struct compLess
{
    bool operator()(const Time &t0, const Time &t1) const
        {
            return (std::abs(t0.getTsec() - t1.getTsec()) >= Time::epsilon) && (t0.getTsec() < t1.getTsec());
        }
};

struct compGreater
{
    bool operator()(const Time &t0, const Time &t1) const
        {
            return (std::abs(t0.getTsec() - t1.getTsec()) >= Time::epsilon) && (t0.getTsec() > t1.getTsec());
        }
};

#endif //TIMES_AND_PLANES_MEASUREUNITS_H
