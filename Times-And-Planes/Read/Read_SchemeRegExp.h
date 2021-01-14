//
// Created by Антон on 10.02.2020.
//

#ifndef TIMES_AND_PLANES_READ_SCHEMEREGEXP_H
#define TIMES_AND_PLANES_READ_SCHEMEREGEXP_H

#include <string>
#include <vector>
#include <Fields of Zone/StandardScheme.h>
#include "Fields of Zone/CheckPoint.h"
#include "Fields of Zone/Scheme.h"

using namespace std;


void
Read_SchemeRegExp(const string &name_of_file, vector<CheckPoint> &checkPoints, vector<Scheme> &schemes, vector<StandardScheme> &standardSchemes);

#endif