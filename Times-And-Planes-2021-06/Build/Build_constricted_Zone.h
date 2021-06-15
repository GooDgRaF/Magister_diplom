//
// Created by Антон on 15.06.2021.
//

#ifndef TIMES_AND_PLANES_2021_06_BUILD_CONSTRICTED_ZONE_H
#define TIMES_AND_PLANES_2021_06_BUILD_CONSTRICTED_ZONE_H

#include <Zone.h>
#include "Fields of Zone/Flow.h"

void build_constricted_Zone(Zone &zone);

void
intersection(const Flow &given_flow, const std::vector<Flow> &flows, std::map<int, std::vector<int>> &pointID_to_mergedFlows, std::vector<int> &flows_start_point); //Возвращает ID первой точки слияния данного потока

#endif //TIMES_AND_PLANES_2021_06_BUILD_CONSTRICTED_ZONE_H
