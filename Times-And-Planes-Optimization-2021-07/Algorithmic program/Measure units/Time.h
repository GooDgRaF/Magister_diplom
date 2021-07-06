//
// Created by Антон on 19.04.2020.
//

#ifndef TIMES_AND_PLANES_TIME_H
#define TIMES_AND_PLANES_TIME_H

#include <vector>
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
    
    double get_sec() const;
    
    double get_sec(const double &round_to) const;
    
    double get_min() const;
    
    double get_min(const double &round_to) const;
    
    static Time create_sec(double sec);
    
    static Time create_min(double min);
    
    static Time create_hour(double hour);
    
    static Time create(double value, std::string_view mu);
    
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
    Time min{Time::create_sec(0)};
    Time max{Time::create_sec(0)};
    
    
    TS(const double t_min, const double t_max, const std::string_view mu = "s") noexcept:
            min(Time::create(t_min, mu)), max(Time::create(t_max, mu))
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
bool isZero(const TS &ts);

bool isIntersection_flag(const TS &ts);// true - если пересечения не было

TS intersection_TS(const TS &ab, const TS &cd);

std::vector<TS> intersection_vTS(const std::vector<TS> &v1, const std::vector<TS> &v2);

#endif //TIMES_AND_PLANES_TIME_H
