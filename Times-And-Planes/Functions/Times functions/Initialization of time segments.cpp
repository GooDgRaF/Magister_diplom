//
// Created by Антон on 21.01.2021.
//

#include <Fields of Zone/Maps.h>
#include "Initialization of time segments.h"
#include "Time segment from point to checkPoint.h"
#include "Calc time segments for StScheme.h"

using namespace std;

void
initialTimes(Flow &flow, const std::vector<CheckPoint> &checkPoints, const PlanePoint &plane, const std::pair<int, int> &edge_ID_ID)
    {
        int& there_ID = pointNameToID[plane.destination];//Записываем ID точки "куда"

        //ВС не на стандартной и нет участка спрямления
        if (edgeTo_ends_str_ID.find(edge_ID_ID) == edgeTo_ends_str_ID.end()) //нет спрямления
        {
            if (edgeTo_stScheme_part.find(edge_ID_ID) == edgeTo_stScheme_part.end())//не на стандартной схеме
            {
                flow.times[there_ID].push_back(plane_checkPoint_Time(plane, checkPoints[there_ID]));// линейный участок
            }
            else //на ст схеме
            calc_and_initStScheme(flow, checkPoints, plane, edge_ID_ID, there_ID);//Обработка ст. схемы
        }
        else // На спрямлении
        {
            int non_str_point = edge_ID_ID.second;
            pair<Time, Time> non_str_point_time = plane_checkPoint_Time(plane, checkPoints[non_str_point]);
            flow.times[non_str_point].push_back(non_str_point_time); // добавили время для точки по path

            for (auto const &str_point : edgeTo_ends_str_ID[edge_ID_ID]) // для всех точек спрямления
            {
                flow.times[str_point].push_back(
                        {plane_checkPoint_Time(plane, checkPoints[str_point]).first //мин время - по кратчайшей наибыстрейше
                                , //макс время - через точку из path самым медленным способом
                         non_str_point_time.second + checkPoint_checkPoint_Time(checkPoints[non_str_point], checkPoints[str_point]).second}
                );
            }
        }
    }