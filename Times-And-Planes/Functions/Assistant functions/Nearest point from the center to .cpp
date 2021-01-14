//
// Created by Антон on 14.01.2021.
//

#include <Fields of Zone/Maps.h>
#include "Nearest point from the center to .h"

std::pair<int,int> nearest_point_origin(const Zone &zone, const PlanePoint &planeP, const std::string &name_of_flow)
    {
        int flowID = flowNameToID[name_of_flow];

        Coordinate sq_rP = planeP.sq_abs();//rP - planes radius-vector, sq - squaring

        int i = -1;
        for (auto point_id : zone.flows[flowID].keys)
        {
            i++;
            CheckPoint checkPoint = zone.checkPoints[point_id];
            Coordinate sq_rcP = checkPoint.sq_abs();

            if (sq_rcP.getMs() < sq_rP.getMs()) //Так как точка (0,0,900м) принадлежит всем потокам, это условие обязательно выполнится
            {
                std::pair<int,int> pair = {i, point_id};
                return pair;
            }
        }
        cerr << "[nearest_point_origin]: Unexpected error, the point is too close to the origin!" << endl;
        std::pair<int,int> pair = {-1, -1};
        return pair;
    }
