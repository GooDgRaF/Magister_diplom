//
// Created by Антон on 21.01.2021.
//

#include "Arc length.h"
#include "Distance between two Points.h"

Distance
arc_length(const Point &start, const Point &second, const Point &plane)//Точка начала дуги, конца и точка между ними
    {
        Point center;
        center.x = 0.5 * (start.x + second.x);
        center.y = 0.5 * (start.y + second.y);
        center.z = 0.5 * (start.z + second.z);

        Distance cp = distancePoint(center, plane);
        Distance cs = distancePoint(center, second);
        Distance sp = distancePoint(second, plane);

        Distance cosC = 0.5 * (cp * cp + cs * cs - sp * sp) / (cp * cs);
        double angle_rad = acos(cosC.getMs());

        return cs * angle_rad;
    }