//
// Created by serge on 12.03.2020.
//

#include "Maps.h"

std::map<std::string, int> pointNameToID;
std::map<std::string, int> flowNameToID;
std::map<int, int> checkPointIDtoStSchemeID;
std::map<int, int> checkPointID_to_waID;
std::map<std::pair<int, int>, std::vector<int>> edgeTo_ends_str_ID;
std::map<std::pair<int, int>, std::pair<StandardScheme, int>> edgeTo_stScheme_part;
