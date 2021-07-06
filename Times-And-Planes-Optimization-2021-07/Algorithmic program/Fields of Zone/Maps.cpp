//
// Created by serge on 12.03.2020.
//

#include "Maps.h"

std::map<std::string, int> pointNameToID;
std::map<std::string, int> flowNameToID;
std::map<int, int> checkPointIDtoStSchemeID;
std::map<int, int> checkPointID_to_waID;
std::map<edge, std::vector<int>> edgeTo_strEnds;
std::map<int, std::vector<int>> pointTo_strStarts;
std::map<std::pair<int, int>, std::pair<StandardScheme, int>> edgeTo_stScheme_part;
