//
// Created by Антон on 25.06.2021.
//

#include "Read and build.h"
#include <iostream>
#include <fstream>
#include "Fields of Zone/Maps.h"
#include <sstream>

//Данные странные числа - сумма символов в ASCII
enum MeasureUnits_Coordinate
{
    meters = 109, //m
    kilometers = 216, //km
    naval_miles = 155, //NM
};

enum MeasureUnits_Velocity
{
    meters_per_second = 319, //m_s
    kilometers_per_hour = 415, //km_h
    naval_miles_per_hour = 354 //NM_h
};
void fill_checkPoint_coordinate(Distance &coordinate_field, const int measure_unit, const double value)
    {
        switch (measure_unit)
        {
            case meters: coordinate_field = Distance::createM(value);
                break;
            case kilometers: coordinate_field = Distance::createKm(value);
                break;
            case naval_miles: coordinate_field = Distance::createNM(value);
                break;
            default: std::cerr << "Error! Wrong unit of coordinate measurement." << std::endl;
                exit(-3);
        }


    }

void fill_checkPoint_velocity(Velocity &velocity_field, const int measure_unit, const double value)
    {
        switch (measure_unit)
        {
            case meters_per_second: velocity_field = Velocity::createVm_s(value);
                break;
            case kilometers_per_hour: velocity_field = Velocity::createVkm_h(value);
                break;
            case naval_miles_per_hour: velocity_field = Velocity::createVNM_h(value);
                break;

            default: std::cerr << "Error! Wrong unit of velocity measurement." << std::endl;
                exit(-3);
        }

    }

void fillScheme(const std::__cxx11::string &str, std::vector<int> &field)
	{
		std::stringstream ss(str);
		std::__cxx11::string token;
		while (ss >> token)
		{
			try
			{
				field.push_back(pointNameToID.at(token));
			}
			catch (const std::out_of_range &ex)
			{
				throw std::runtime_error(token);
			}
		}
	}

void sum_char_mu(const std::string &str, std::vector<int> &v)
    {
        std::stringstream ss(str);
        std::string token;
        while (ss >> token)
        {
            int sum = 0;
            for (auto c : token)
            {
                sum += c;
            }
            v.push_back(sum);
        }
    }

void openFile(const std::__cxx11::string &name_of_file, std::ifstream &openfile)
{
    openfile.open(name_of_file);

    if (openfile.is_open())
    {
        std::cout << "File " << name_of_file << " is open!" << std::endl;
    }
    else
    {
        std::cerr << "Error! Can't open " << name_of_file << std::endl;
        exit(-1) ;
    }
}