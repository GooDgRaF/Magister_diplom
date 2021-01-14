//
// Created by Антон on 14.01.2021.
//

#include "Distance between two Points.h"

Coordinate distancePoint(const Point &p1, const Point &p2)
    {
        return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
    }
