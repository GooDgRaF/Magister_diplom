//
// Created by Антон on 14.01.2021.
//

#include <Fields of Zone/Maps.h>
#include <Functions/Assistant functions/Nearest point from the center to .h>
#include <Functions/Assistant functions/Distance between two Points.h>
#include "Calculate times new plane.h"
#include "Calculate times.h"

std::pair<Time, Time> initialTime(const PlanePoint &plane, const CheckPoint &point_there)
    {
        Coordinate d = distancePoint(plane, point_there);
        Time T_initial_min = 2 * d / (plane.V + point_there.Vmax);
        Time T_initial_max = 2 * d / (plane.V + point_there.Vmin);

        return {T_initial_min,T_initial_max};
    }

/*
 Функция принимает на вход Зону, структуру типа (x,y,z,v), имя потока,
к которому отнесли данное ВС и два имени контрольных точек Зоны: откуда и куда оно летит.

*/


void calc_plane(Zone &zone, const PlanePoint &plane, string &flow_name,
           string &check_point_there, std::pair<string, string> &edge_plane)
    {
        pair<int, int> edge_ID_ID = {pointNameToID[edge_plane.first], pointNameToID[edge_plane.second]};
        int ID_there = pointNameToID[check_point_there];

        const CheckPoint &point_there = zone.checkPoints[ID_there];
        Flow &flow = zone.flows[flowNameToID[flow_name]];
        flow.times[ID_there].push_back(initialTime(plane, point_there));

        bool allowed_str = false;
        if (allowed_str)//TODO Понять, можно ли спрямляться с данного ребра.
        {
            vector<int> ID_end_str_points;
            for (auto ID_end_str_point : ID_end_str_points)
            {
                flow.times[ID_end_str_point].push_back(initialTime(plane, zone.checkPoints[ID_end_str_point]));

            }
        }


//Ищем номер вершины "куда" в топологичеком порядке потока
        auto it_index_there = find(flow.keys.begin(), flow.keys.end(), ID_there);
        int top_ID_there = it_index_there - flow.keys.begin();


        calculateTimes(zone, flow, top_ID_there);

    }
