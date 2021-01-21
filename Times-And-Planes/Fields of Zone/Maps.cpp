//
// Created by serge on 12.03.2020.
//

#include "Maps.h"

std::map<std::string, int> pointNameToID;
std::map<std::string, int> flowNameToID;
std::map<int, int> checkPointIDtoStSchemeID;
std::map<std::pair<int, int>, std::vector<int>> edgeTo_ends_str_ID;
std::map<std::pair<int, int>, std::pair<int, int>> edgeTo_stScheme_nextChPointID_ordinal;
