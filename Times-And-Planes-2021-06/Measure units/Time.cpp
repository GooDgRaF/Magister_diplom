//
// Created by Антон on 19.04.2020.
//

#include <cmath>
#include "Time.h"
#include "Distance.h"
#include "Velocity.h"
#include "MeasureUnits.h"

double Time::getTsec() const
    {
        return time_sec;
    }

double Time::getTsec(const double &round_to) const
    {
        return round(time_sec*round_to)/round_to;
    }

double Time::getTmin() const
    {
        return time_sec/min2sec;
    }

double Time::getTmin(const double &round_to) const
    {
        return round(time_sec/min2sec*round_to)/round_to;
    }

Time Time::createTsec(double sec)
    {
        return Time(sec);
    }

Time Time::createTmin(double min)
    {
        return Time(min*min2sec);
    }

Time Time::operator+() const
    {
        return Time(time_sec);
    }

Time Time::operator-() const
    {
        return Time(-time_sec);
    }

std::ostream &operator<<(std::ostream &out, const Time &t)
    {
        out << t.getTsec(1);
        //out << t.getTmin(100) << " min";
        //out << t.getTsec(100)/3600 << " hours";
        return out;
    }

bool operator<(const Time &t0, const Time &t1)
    {
        return (std::abs(t0.getTsec() - t1.getTsec()) >= Time::epsilon) && (t0.getTsec() < t1.getTsec());
    }

bool operator==(const Time &t0, const Time &t1)
    {
        return abs(t0.getTsec() - t1.getTsec()) < Time::epsilon;
    }

bool operator<=(const Time &t0, const Time &t1)
    {
        return t0 < t1 || t0 == t1;
    }

Time operator/(const Distance &x, const Velocity &v)
    {
        return Time::createTsec(x.getMs()/v.getVm_s());
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
        return Time::createTsec(a*t.getTsec());
    }

Time operator*(const Time &t, const double &a)
    {
        return Time::createTsec(t.getTsec()*a);
    }


TS operator*(const double &a, const TS &ts)
    {
        return {a*ts.min, a*ts.max};
    }

TS operator*(const int &a, const TS &ts)
    {
        return {a*ts.min, a*ts.max};
    }

TS operator*(const TS &ts, const double &a)
    {
        return a*ts;
    }

TS operator*(const TS &ts, const int &a)
    {
        return a*ts;
    }

TS operator+(const TS &l_ts, const TS &r_ts)
    {
        return TS(l_ts.min + r_ts.min, l_ts.max + r_ts.max);
    }

std::ostream &operator<<(std::ostream &out, const TS &ts)
    {
        return out << "[" << ts.min << ", " << ts.max << "] ";
    }

TS intersection_TS(const TS &ab, const TS &cd)
    {
        TS zero_TS{0, 0};
        double a = ab.min.getTsec(), b = ab.max.getTsec(), c = cd.min.getTsec(), d = cd.max.getTsec();
        
        if (((c < a) && (a <= d) && (d < b)))//c < a <= d < b
            return {Time::createTsec(a), Time::createTsec(d)};
        if (((a < c) && (c <= b) && (b < d)))//a < c <= b < d
            return {Time::createTsec(c), Time::createTsec(b)};
        if (((a <= c) && (c <= d) && (d <= b)))//a <= c <= d <= b
            return {Time::createTsec(c), Time::createTsec(d)};
        if (((c <= a) && (a <= b) && (b <= d))) //c <= a <= b <= d
            return {Time::createTsec(a), Time::createTsec(b)};
        return zero_TS;
    }
    

