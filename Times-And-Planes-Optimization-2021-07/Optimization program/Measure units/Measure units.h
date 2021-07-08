//
// Created by Антон on 07.07.2021.
//

#ifndef TIMES_AND_PLANES_OPTIMIZATION_2021_07_MEASURE_UNITS_H
#define TIMES_AND_PLANES_OPTIMIZATION_2021_07_MEASURE_UNITS_H

#include "string_view"
#include "cassert"

struct Coordinate
{
    double meter{0}; //В метрах
    Coordinate(const double value, const std::string_view mu = "m") noexcept
        {
            if (mu == "m")
                meter = value;
            else if (mu == "km")
                meter = value*km2m;
            else if (mu == "NM")
                meter = value*NMs2m;
            else
                assert(false &&
                       "Check the correctness of the entered units of measurement: it should be --> 'm' - meters, 'km' - kilometers, 'NM' - naval miles");
        };

    double getM() const
        {
            return meter;
        }

    double getKm() const
        {
            return meter/km2m;
        }

    double getNM() const
        {
            return meter/NMs2m;
        }


private:
    static constexpr double km2m = 1000;
    static constexpr double NMs2m = 1852;
};

struct Velocity
{
    double meters_per_second{0}; //В метрах в секунду

    Velocity(const double value, const std::string_view mu = "m_s") noexcept
        {
            assert(value >= 0 && "Velocity can not be negative!");

            if (mu == "m_s")
                meters_per_second = value;
            else if (mu == "km_h")
                meters_per_second = value*m_s2km_h;
            else if (mu == "NM_h")
                meters_per_second = value*m_s2NM_h;
            else
                assert(false &&
                       "Check the correctness of the entered units of measurement: it should be --> 'm_s' - meters per second, 'km_h' - kilometers per hour, 'NM_h' - naval miles per hour");
        };

private:
    static constexpr double m_s2km_h = 3.6;
    static constexpr double m_s2NM_h = 1.94;
};
//
//struct Time
//{
//    double time_sec; //В секундах
//
//    Time(const double value, const std::string_view mu = "s") noexcept
//        {
//            assert(value >= 0 && "Time can not be negative!");
//
//            if (mu == "m_s")
//                meters_per_second = value;
//            else if (mu == "km_h")
//                meters_per_second = value*m_s2km_h;
//            else if (mu == "NM_h")
//                meters_per_second = value*m_s2NM_h;
//            else
//                assert(false &&
//                       "Check the correctness of the entered units of measurement: it should be --> 'm_s' - meters per second, 'km_h' - kilometers per hour, 'NM_h' - naval miles per hour");
//        };
//private:
//    static constexpr double _2sec = 60;
//    static constexpr double epsilon = 0.0001; //Точность сравнения
//};
//
//Distance operator+(const Distance &l_d, const Distance &r_d);
//
//Distance operator-(const Distance &l_d, const Distance &r_d);
//
//Distance operator*(const Time &l_t, const Velocity &r_v);
//
//Distance operator*(const Velocity &l_v, const Time &r_t);
//
////TODO Космический корабль приди, порядок наведи
//
//Distance operator*(const double &a, const Distance &r_d);
//
//Distance operator*(const Distance &l_d, const double &a);
//
//Distance operator*(const Distance &l_d, const Distance &r_d);
//
//Distance operator/(const Distance &l_d, const Distance &r_d);
//
//Distance pow(Distance x, int a);
//
//Distance sqrt(Distance x);
//
////Скорости
//
//Velocity operator+(const Velocity &l_v, const Velocity &r_v);
//
//Velocity operator-(const Velocity &l_v, const Velocity &r_v);
//
//Velocity operator/(const Distance &l_d, const Time &t);
//
//Velocity operator*(const double &a, const Velocity &r_v);
//
//Velocity operator*(const Velocity &l_v, const double &a);
//
//Time operator/(const Distance &l_d, const Velocity &v);
//
//Time operator+(const Time &t0, const Time &t1);
//
//Time operator-(const Time &t0, const Time &t1);
//
//Time operator*(const double &a, const Time &t);
//
//Time operator*(const Time &t, const double &a);
//
//
#endif //TIMES_AND_PLANES_OPTIMIZATION_2021_07_MEASURE_UNITS_H
