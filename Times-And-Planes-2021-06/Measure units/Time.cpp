//
// Created by Антон on 19.04.2020.
//

#include <cmath>
#include "Time.h"
#include "Distance.h"
#include "Velocity.h"
using TS = std::pair<Time, Time>; //TS - time segments - временные интервалы


Time::Time(double d)
    {
        time_sec = d;
    }

double Time::getTsec() const
    {
        return time_sec;
    }

double Time::getTsec(const double &round_to) const
    {
        return round(time_sec * round_to) / round_to;
    }

double Time::getTmin() const
    {
        return time_sec / min2sec;
    }

double Time::getTmin(const double &round_to) const
    {
        return round(time_sec / min2sec * round_to) / round_to;
    }

Time Time::createTsec(double sec)
    {
        return {sec};
    }

Time Time::createTmin(double min)
    {
        return {min * min2sec};
    }

Time Time::operator+()
    {
        return {time_sec};
    }

Time Time::operator-()
    {
        return {-time_sec};
    }

std::ostream &operator<<(std::ostream &out, const Time &t)
    {
        out << t.getTsec(1);
        //out << t.getTmin(100) << " min";
        //out << t.getTsec(100)/3600 << " hours";
        return out;
    }

TS Time::create_zero_TS()
    {
        return {Time::createTsec(0), Time::createTsec(0)};
    }

Time operator/(const Distance &x, const Velocity &v)
    {
        return Time::createTsec(x.getMs() / v.getVm_s());
    }

Time operator+(const Time &t0, const Time &t1)
    {
        return Time::createTsec(t0.getTsec() + t1.getTsec());
    }

Time operator-(const Time &t0, const Time &t1)
    {
        return Time::createTsec(t0.getTsec() - t1.getTsec());
    }

Time operator*(const double &a, const Time &t)
    {
        return Time::createTsec(a * t.getTsec());
    }

Time operator*(const Time &t, const double &a)
    {
        return Time::createTsec(t.getTsec() * a);
    }

TS operator+(const TS &x, const TS &y)
    {
        return {x.first + y.first, x.second + y.second};
    }


TS operator*(const double &a, const TS &ts)
    {
        return {a * ts.first, a * ts.second};
    }

TS operator*(const int &a, const TS &ts)
    {
        return {a * ts.first, a * ts.second};
    }

TS operator*(const TS &ts, const double &a)
    {
        return a * ts;
    }
TS operator*(const TS &ts, const int &a)
    {
        return a * ts;
    }


std::ostream &operator<<(std::ostream &out, const TS &pair)
    {
        return std::cout << "[" << pair.first << ", " << pair.second << "] ";
    }
