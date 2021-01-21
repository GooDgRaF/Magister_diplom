//
// Created by Антон on 07.05.2020.
//

#include "Calculate standard scheme.h"
#include "Arc length.h"
#include "Distance between two Points.h"
#include <Functions/Times functions/Arc time.h>

void calcStScheme(vector<CheckPoint> &checkPoints, StandardScheme &stScheme)
    {
        stScheme.start = checkPoints[stScheme.start_ID];
        stScheme.second = checkPoints[stScheme.second_ID];
        stScheme.third = checkPoints[stScheme.third_ID];

        Distance semicircle = arc_length(stScheme.start, stScheme.second, stScheme.start);
        Distance line = distancePoint(stScheme.second, stScheme.third);
//TODO Принять решение о необходимости использовать функцию полукруг Тмин
        stScheme.Tmin = semicircle_Time(stScheme.start, stScheme.second).first;
        stScheme.Tmax = 2 * (semicircle + line) / stScheme.start.Vmin;
    }
