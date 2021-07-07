//
// Created by Антон on 07.07.2021.
//

#ifndef TIMES_AND_PLANES_OPTIMIZATION_2021_07_MEASURE_UNITS_H
#define TIMES_AND_PLANES_OPTIMIZATION_2021_07_MEASURE_UNITS_H

#include "string_view"
#include "cassert"

struct Distance
{
    double meter{0}; //В метрах
    Distance(const double value, const std::string_view mu) noexcept
        {
            assert(value >= 0 && "Distance can not be negative!");
            
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
    
    friend Distance operator+(const Distance &l_d, const Distance &r_d);
    
    friend Distance operator-(const Distance &l_d, const Distance &r_d);


private:
    static constexpr double km2m = 1000;
    static constexpr double NMs2m = 1852;
};



#endif //TIMES_AND_PLANES_OPTIMIZATION_2021_07_MEASURE_UNITS_H
