//
// Created by Антон on 21.02.2020.
//

#ifndef TIMES_AND_PLANES_MAPS_H
#define TIMES_AND_PLANES_MAPS_H

#include <string>
#include <vector>
#include <map>
#include "StandardScheme.h"


extern std::map<std::string, int> pointNameToID;
extern std::map<std::string, int> flowNameToID;
extern std::map<int, int> checkPointIDtoStSchemeID;
extern std::map<std::pair<int, int>, std::vector<int>> edgeTo_ends_str_ID;
extern std::map<std::pair<int, int>,
        std::pair<StandardScheme, int>>
        edgeTo_stScheme_part;//Отображение Ребро --> Соответствующая ст. схема, порядковый номер ребра в ст схеме

#endif //TIMES_AND_PLANES_MAPS_H
