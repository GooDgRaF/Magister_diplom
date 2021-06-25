////
//// Created by Антон on 07.05.2020.
////
//
//#include "Calculate standard scheme.h"
//#include "Arc length.h"
//#include "Distance between two Points.h"
//#include "Calculate_times.h"
//#include <Functions/Times functions/Time segment from point to checkPoint.h>
//#include <Fields of Zone/Maps.h>
//#include <Functions/Times functions/Calculate_times.h>
//
//using namespace std;
//
//void fill_StScheme(vector<CheckPoint> &checkPoints, StandardScheme &stScheme)
//    {
//        stScheme.start = checkPoints[stScheme.start_ID];
//        stScheme.second = checkPoints[stScheme.second_ID];
//        stScheme.third = checkPoints[stScheme.third_ID];
//        stScheme.end = checkPoints[stScheme.end_ID];
//
//        //Первая полуокружность и обратная прямая
//        Distance semicircle_first = arc_length(stScheme.start, stScheme.second, stScheme.start);
//        stScheme.first_semicircle_length = semicircle_first;
//        stScheme.first_semicircle_T = semicircle_Time(stScheme.start, stScheme.second);
//        Distance line_back = distancePoint(stScheme.second, stScheme.third);
//        stScheme.line_back = line_back;
//        stScheme.line_back_T = checkPoint_checkPoint_Time(stScheme.second, stScheme.third);
//
//        //Вторая полуокружность и прямая
//        Distance semicircle_second = arc_length(stScheme.third, stScheme.end, stScheme.third);
//        stScheme.second_semicircle_length = semicircle_second;
//        stScheme.second_semicircle_T = semicircle_Time(stScheme.third, stScheme.end);
//        Distance line_forward = distancePoint(stScheme.end, stScheme.start);
//        stScheme.line_forward = line_forward;
//        stScheme.line_forward_T = checkPoint_checkPoint_Time(stScheme.end, stScheme.start);
//
//
//        stScheme.Tmin = 2 * 2 * semicircle_first /
//                        (stScheme.start.Vmax + stScheme.second.Vmax); //Длина окружности на скорость
//        stScheme.Tmax = 4 * (semicircle_first + line_back
//                         + semicircle_second + line_forward)
//                        / (stScheme.start.Vmin + stScheme.second.Vmin + stScheme.third.Vmin + stScheme.end.Vmin);
//
//        stScheme.min_max_time = {stScheme.Tmin, stScheme.Tmax};
//
//
//        edgeTo_stScheme_part[{stScheme.start_ID, stScheme.second_ID}] = {stScheme, 1};
//        edgeTo_stScheme_part[{stScheme.second_ID, stScheme.third_ID}] = {stScheme, 2};
//        edgeTo_stScheme_part[{stScheme.third_ID, stScheme.end_ID}] = {stScheme, 3};
//    }
