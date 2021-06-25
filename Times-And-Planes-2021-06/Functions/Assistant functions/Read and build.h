//
// Created by Антон on 25.06.2021.
//

#ifndef TIMES_AND_PLANES_2021_06_READ_AND_BUILD_H
#define TIMES_AND_PLANES_2021_06_READ_AND_BUILD_H

#include <string>
#include <vector>
#include <map>
#include "Fields of Zone/Point.h"

void fill_checkPoint_coordinate(Distance &coordinate_field, const int measure_unit, const double value);

void fill_checkPoint_velocity(Velocity &velocity_field, const int measure_unit, const double value);

void fillScheme(const std::string &str, std::vector<int> &field);

void sum_char_mu(const std::string &str, std::vector<int> &v);

void openFile(const std::string &name_of_file, std::ifstream &openfile);

#include "Fields of Zone/Point.h"

#endif //TIMES_AND_PLANES_2021_06_READ_AND_BUILD_H
