//
// Created by Антон on 14.01.2021.
//

#include <Fields of Zone/Maps.h>
#include <Functions/Assistant functions/Nearest point from the center to .h>
#include <Functions/Assistant functions/Distance between two Points.h>
#include "Calculate times new plane.h"
#include "Calculate times.h"

void calc_new_plane(Zone &zone, const PlanePoint &plane, string &flow_name)
    {
        std::pair<int, int> pair_topID_checkPID = nearest_point_origin(zone, plane, flow_name);

        Coordinate d = distancePoint(plane, zone.checkPoints[pair_topID_checkPID.second]);
        Time T_initial = d/plane.V;

        Flow &flow =  zone.flows[flowNameToID[flow_name]];
        flow.times[pair_topID_checkPID.first].push_back({T_initial,T_initial});

//        cout << flow.times[pair_topID_checkPID.first][0].first;
//        cout << zone.flows[flowNameToID[flow_name]].times[pair_topID_checkPID.first][0].first;


        calculateTimes(zone,flow,pair_topID_checkPID.first);

    }
