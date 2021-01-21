//
// Created by Антон on 21.01.2021.
//

#include <Fields of Zone/Maps.h>
#include "Initialization of time segments.h"
#include "Time segment from point to checkPoint.h"

void
initialTimes(Flow &flow, const vector<CheckPoint> &checkPoints, const PlanePoint &plane, const pair<int, int> &edge_ID_ID, const int ID_there)
    {
        if (edgeTo_ends_str_ID.find(edge_ID_ID) != edgeTo_ends_str_ID.end())//Если с ребра возможно спрямление
        {
            const vector<int> ID_end_str_points = edgeTo_ends_str_ID[edge_ID_ID];
            for (auto ID_end_str_point : ID_end_str_points)
            {
                flow.times[ID_end_str_point].push_back(plane_checkPoint_Time(plane, checkPoints[ID_end_str_point]));
            }
        }
        if (ID_there == edge_ID_ID.second)//Если не совпал, то этот временной интервал уже записан ранее
        {
            const CheckPoint &point_there = checkPoints[ID_there];
            flow.times[ID_there].push_back(plane_checkPoint_Time(plane, point_there));
        }
    }