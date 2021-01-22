//
// Created by Антон on 07.05.2020.
//

#include "Calculate standard scheme.h"
#include "Arc length.h"
#include "Distance between two Points.h"
#include <Functions/Times functions/Arc time.h>
#include <Functions/Times functions/Time segment from point to checkPoint.h>
#include <Fields of Zone/Maps.h>

void fill_StScheme(vector<CheckPoint> &checkPoints, StandardScheme &stScheme)
    {
        stScheme.start = checkPoints[stScheme.start_ID];
        stScheme.second = checkPoints[stScheme.second_ID];
        stScheme.third = checkPoints[stScheme.third_ID];

        Distance semicircle = arc_length(stScheme.start, stScheme.second, stScheme.start);
        stScheme.semicircle_length = semicircle;

        stScheme.semicircle_T = semicircle_Time(stScheme.start, stScheme.second);

        Distance line = distancePoint(stScheme.second, stScheme.third);
        stScheme.line = line;

        stScheme.line_T = checkPoint_checkPoint_Time(stScheme.second, stScheme.third);

        stScheme.Tmin = 2 * semicircle / stScheme.start.Vmax;
        stScheme.Tmax = 2 * (semicircle + line) / stScheme.start.Vmin;


        edgeTo_stScheme_part[{stScheme.start_ID, stScheme.second_ID}] = {stScheme, 1};
        edgeTo_stScheme_part[{stScheme.second_ID, stScheme.third_ID}] = {stScheme, 2};
        edgeTo_stScheme_part[{stScheme.third_ID, stScheme.start_ID}] = {stScheme, 3};
    }
