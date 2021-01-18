//
// Created by Антон on 21.02.2020.
//

#ifndef TIMES_AND_PLANES_MAPS_H
#define TIMES_AND_PLANES_MAPS_H

#include <string>
#include <vector>
#include <map>


extern std::map<std::string, int> pointNameToID;
extern std::map<std::string, int> flowNameToID;
extern std::map<int, int> checkPointIDtoStSchemeID;
extern std::map<std::pair<int, int>, std::vector<int>> edgeTo_ends_str_ID;

#endif //TIMES_AND_PLANES_MAPS_H
