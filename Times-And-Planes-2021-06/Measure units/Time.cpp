//
// Created by Антон on 19.04.2020.
//

#include <cmath>
#include "Time.h"
#include "Distance.h"
#include "Velocity.h"
#include "MeasureUnits.h"

double Time::get_sec() const
    {
        return time_sec;
    }

double Time::get_sec(const double &round_to) const
    {
        return round(time_sec*round_to)/round_to;
    }

double Time::get_min() const
    {
        return time_sec/min2sec;
    }

double Time::get_min(const double &round_to) const
    {
        return round(time_sec/min2sec*round_to)/round_to;
    }

Time Time::create_sec(double sec)
    {
        return Time(sec);
    }

Time Time::create_min(double min)
    {
        return Time(min*min2sec);
    }

Time Time::create_hour(double hour)
    {
        return Time(hour*min2sec*min2sec);
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
        out << t.get_sec(1);
        //out << t.getTmin(100) << " min";
        //out << t.getTsec(100)/3600 << " hours";
        return out;
    }

bool operator<(const Time &t0, const Time &t1)
    {
        return (std::abs(t0.get_sec() - t1.get_sec()) >= Time::epsilon) && (t0.get_sec() < t1.get_sec());
    }

bool operator==(const Time &t0, const Time &t1)
    {
        return abs(t0.get_sec() - t1.get_sec()) < Time::epsilon;
    }

bool operator<=(const Time &t0, const Time &t1)
    {
        return t0 < t1 || t0 == t1;
    }

Time Time::create(double value, const std::string &mu)
    {
        if (mu == "s")
        { return create_sec(value); }
        if (mu == "min")
        { return create_min(value); }
        if (mu == "h")
        { return create_hour(value); }
        else std::cerr << "Was created a nonvalid object!"
                          " MU must be: 's' or 'min' or 'h'. But MU was: " << mu << std::endl;
        return create_sec(-1);
    }

Time operator/(const Distance &x, const Velocity &v)
    {
        return Time::create_sec(x.getMs()/v.getVm_s());
    }

Time operator+(const Time &t0, const Time &t1)
    {
        return Time::create_sec(t0.get_sec() + t1.get_sec());
    }

Time operator-(const Time &t0, const Time &t1)
    {
        return Time::create_sec(t0.get_sec() - t1.get_sec());
    }

Time operator*(const double &a, const Time &t)
    {
        return Time::create_sec(a*t.get_sec());
    }

Time operator*(const Time &t, const double &a)
    {
        return Time::create_sec(t.get_sec()*a);
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
        double a = ab.min.get_sec(), b = ab.max.get_sec(), c = cd.min.get_sec(), d = cd.max.get_sec();
        
        if (((c < a) && (a <= d) && (d < b)))//c < a <= d < b
            return {Time::create_sec(a), Time::create_sec(d)};
        if (((a < c) && (c <= b) && (b < d)))//a < c <= b < d
            return {Time::create_sec(c), Time::create_sec(b)};
        if (((a <= c) && (c <= d) && (d <= b)))//a <= c <= d <= b
            return {Time::create_sec(c), Time::create_sec(d)};
        if (((c <= a) && (a <= b) && (b <= d))) //c <= a <= b <= d
            return {Time::create_sec(a), Time::create_sec(b)};
        return zero_TS;
    }
    

