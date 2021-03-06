//
// Created by Антон on 19.04.2020.
//

#include <cmath>
#include "Time.h"
#include "Distance.h"
#include "Velocity.h"


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

std::pair<Time, Time> operator+(const std::pair<Time, Time> &x, const std::pair<Time, Time> &y)
    {
        return {x.first + y.first, x.second + y.second};
    }

std::ostream &operator<<(std::ostream &out, const std::pair<Time, Time> &pair)
    {
       return std::cout << "[" << pair.first << ", " << pair.second << "] ";
    }
