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

        return {T_initial_min, T_initial_max};
    }

/*
 Функция принимает на вход Зону, структуру типа (x,y,z,v), имя потока,
к которому отнесли данное ВС, контрольную точу куда оно летит и ещё две КТ,
образующие рербро на котором в данный моент находится ВС.
*/


int calc_plane(Zone &zone, const PlanePoint &plane, const string &flow_name,
               const string &check_point_there, const pair<string, string> &edge_plane_point)
    {
        try
        {
            pointNameToID.at(check_point_there);
            pointNameToID.at(edge_plane_point.first);
            pointNameToID.at(edge_plane_point.second);
        }
        catch (const out_of_range &ex) //Ловим ошибку о не обнаружении точки среди точек из checkPoints
        {
            cerr << "Can't find '"
                 << check_point_there << "' or '"
                 << edge_plane_point.first << "' or '"
                 << edge_plane_point.second << "' among points from Points file" << endl;
            return -1;
        }

        Flow &flow = zone.flows[flowNameToID[flow_name]];
        const pair<int, int> edge_ID_ID = {pointNameToID[edge_plane_point.first],
                                           pointNameToID[edge_plane_point.second]};
        if (edgeTo_ends_str_ID.find(edge_ID_ID) != edgeTo_ends_str_ID.end())//Если с ребра возможно спрямление
        {
            const vector<int> ID_end_str_points = edgeTo_ends_str_ID[edge_ID_ID];
            for (auto ID_end_str_point : ID_end_str_points)
            {
                flow.times[ID_end_str_point].push_back(initialTime(plane, zone.checkPoints[ID_end_str_point]));
            }
        }


        const int ID_there = pointNameToID[check_point_there];//Записываем начальное значение времени для точки "куда"
        if (ID_there == edge_ID_ID.second)//Если не совпал, то этот временной интервал уже записан ранее
        {
            const CheckPoint &point_there = zone.checkPoints[ID_there];
            flow.times[ID_there].push_back(initialTime(plane, point_there));
        }


//Ищем номер вершины "куда" в топологичеком порядке потока
        auto it_index_there = find(flow.keys.begin(), flow.keys.end(), ID_there);
        const int top_ID_there = it_index_there - flow.keys.begin();


        calculateTimes(zone, flow, top_ID_there);//Рассчитываем все времена, которые "ниже по течению"
        return 0;
    }
