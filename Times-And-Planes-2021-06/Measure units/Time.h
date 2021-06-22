//
// Created by Антон on 19.04.2020.
//

#ifndef TIMES_AND_PLANES_TIME_H
#define TIMES_AND_PLANES_TIME_H

#include "iostream"
#include "cassert"

class Time
{
    double time_sec; //В секундах
    explicit Time(double d) : time_sec{d}
        {};

public:
    static constexpr double min2sec = 60;
    
    static constexpr double epsilon = 0.0001; //Точность сравнения
    
    double getTsec() const;
    
    double getTsec(const double &round_to) const;
    
    double getTmin() const;
    
    double getTmin(const double &round_to) const;
    
    static Time createTsec(double sec);
    
    static Time createTmin(double min);
    
    Time operator+() const;
    
    Time operator-() const;
    
    friend bool operator<(const Time &t0, const Time &t1);
    
    friend bool operator==(const Time &t0, const Time &t1);
    
    friend bool operator<=(const Time &t0, const Time &t1);
    //TODO Когда-нибудь тут появится космический корабль <=>
    
    friend std::ostream &operator<<(std::ostream &out, const Time &t);
};

class TS
{
public:
    Time min{Time::createTsec(0)};
    Time max{Time::createTsec(0)};
    
    
    TS(const double t_min, const double t_max) noexcept:
            min(Time::createTsec(t_min)), max(Time::createTsec(t_max))
        {
            assert(t_min <= t_max);
        };
    
    TS(const Time &t_min, const Time &t_max) noexcept:
            min(t_min), max(t_max)
        {
            assert((t_min <= t_max));
        };
    
    friend TS operator+(const TS &l_ts, const TS &r_ts);
    
    friend TS operator*(const double &a, const TS &ts);
    
    friend TS operator*(const int &a, const TS &ts);
    
    friend TS operator*(const TS &ts, const double &a);
    
    friend TS operator*(const TS &ts, const int &a);
    
    friend std::ostream &operator<<(std::ostream &out, const TS &ts);
    
    
};

TS intersection_TS(const TS &ab, const TS &cd);

#endif //TIMES_AND_PLANES_TIME_H
