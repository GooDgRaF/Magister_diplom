//
// Created by Антон on 10.02.2020.
//

#ifndef TIMES_AND_PLANES_SCHEME_H
#define TIMES_AND_PLANES_SCHEME_H

#include <string>
#include <vector>
#include "Point.h"

struct Scheme
{
    std::string name;
    int start;
    std::vector<int> end;
    std::vector<int> path;
    std::vector<int> straighteningFrom;
    std::vector<int> straighteningWhere;
};

#endif //TIMES_AND_PLANES_SCHEME_H
