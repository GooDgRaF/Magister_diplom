//
// Created by Антон on 21.01.2021.
//

#include <Functions/Geometric functions/Distance between two Points.h>
#include "Time segment from point to checkPoint.h"

TS plane_checkPoint_Time(const PlanePoint &plane, const CheckPoint &point_there)
    {
        Distance d = distancePoint(plane, point_there);
        Time T_initial_min = 2 * d / (plane.V + point_there.Vmax);
        Time T_initial_max = 2 * d / (plane.V + point_there.Vmin);

        return {T_initial_min, T_initial_max};
    }

TS checkPoint_checkPoint_Time(const CheckPoint &point_from, const CheckPoint &point_there)
    {
        Distance d = distancePoint(point_from, point_there);
        Time T_initial_min = 2 * d / (point_from.Vmax + point_there.Vmax);
        Time T_initial_max = 2 * d / (point_from.Vmin + point_there.Vmin);

        return {T_initial_min, T_initial_max};
    }
