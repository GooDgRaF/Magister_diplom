//
// Created by Антон on 21.01.2021.
//

#include <Functions/Geometric functions/Arc length.h>
#include "Arc time.h"

std::pair<Time, Time> plane_arc_Time(const CheckPoint &start, const CheckPoint &second, const PlanePoint &plane)
    {
        Distance arc = arc_length(start, second, plane);

        Time T_initial_min = 2 * arc / (plane.V + second.Vmax);
        Time T_initial_max = 2 * arc / (plane.V + second.Vmin);

        return {T_initial_min, T_initial_max};
    }

std::pair<Time, Time> semicircle_Time(const CheckPoint &start, const CheckPoint &second)
    {
        Distance semicircle = arc_length(start, second, start);
        Time T_min = 2 * semicircle / (start.Vmax + second.Vmax);
        Time T_max = 2 * semicircle / (start.Vmin + second.Vmin);


        return {T_min, T_max};
    }
