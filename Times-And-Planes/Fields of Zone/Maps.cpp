//
// Created by serge on 12.03.2020.
//

#include "Maps.h"

std::map<std::string, int> pointNameToID;
std::map<std::string, int> flowNameToID;
std::map<int, int> checkPointIDtoStSchemeID;
std::map<std::pair<int, int>, std::vector<int>> edgeTo_end_str_ID;
