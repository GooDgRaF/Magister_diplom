//
// Created by Антон on 21.02.2020.
//

#ifndef TIMES_AND_PLANES_MAPS_H
#define TIMES_AND_PLANES_MAPS_H

#include <string>
#include <vector>
#include <map>
#include "Waiting area.h"


extern std::map<std::string, int> pointNameToID;
extern std::map<std::string, int> flowNameToID;
extern std::map<int, int> checkPointIDtoStSchemeID;
extern std::map<int, int> checkPointID_to_waID; //wa- waiting area. ID точки --> ID Зоны Ожидания
extern std::map<std::pair<int, int>, std::vector<int>> edgeTo_ends_str_ID;//Ребро --> точки на которые можно спрямиться с этого ребра
extern std::map<std::pair<int, int>,
        std::pair<StandardScheme, int>>
        edgeTo_stScheme_part;//Отображение Ребро --> Соответствующая ст. схема, порядковый номер ребра в ст схеме

#endif //TIMES_AND_PLANES_MAPS_H
