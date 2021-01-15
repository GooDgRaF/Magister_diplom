//
// Created by Антон on 14.01.2021.
//

#include <Fields of Zone/Maps.h>
#include <Functions/Assistant functions/Nearest point from the center to .h>
#include <Functions/Assistant functions/Distance between two Points.h>
#include "Calculate times new plane.h"
#include "Calculate times.h"
/*
 Функция принимает на вход Зону, структуру типа (x,y,z,v) и имя потока,
к которому отнесли данное ВС
 Сначала берётся первая точка из потока (её ID и ID в топологическом порядке данного потока),
которая ближе к началу координат чем ВС.
 Затем в map-времён записывается пара (ID ближайшей точки --> [T,T]),
где T - время, за которое долетит ВС до точки при прямолинейном движении.
 Далее запускается процещдура рассчёта времён для точек "ниже по течению" потока с начальным значением [T,T].
*/

void calc_new_plane(Zone &zone, const PlanePoint &plane, string &flow_name)
    {
        std::pair<int, int> pair_topID_checkPID = nearest_point_origin(zone, plane, flow_name);

        Coordinate d = distancePoint(plane, zone.checkPoints[pair_topID_checkPID.second]);
        Time T_initial = d / plane.V;

        Flow &flow = zone.flows[flowNameToID[flow_name]];
        flow.times[pair_topID_checkPID.second].push_back({T_initial, T_initial});

        calculateTimes(zone, flow, pair_topID_checkPID.first);

    }
