//
// Created by Антон on 10.02.2020.
//

#ifndef TIMES_AND_PLANES_READ_SCHEMEREGEXP_H
#define TIMES_AND_PLANES_READ_SCHEMEREGEXP_H

#include <string>
#include <vector>
#include <Fields of Zone/Waiting area.h>
#include "Fields of Zone/Point.h"
#include "Fields of Zone/Scheme.h"

void
Read_SchemesRegExp(const std::string &name_of_file, std::vector<CheckPoint> &checkPoints,
                   std::vector<Scheme> &schemes, std::vector<StandardScheme> &standardSchemes);

#endif