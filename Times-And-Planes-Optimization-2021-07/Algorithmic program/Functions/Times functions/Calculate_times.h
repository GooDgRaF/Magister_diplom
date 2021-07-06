//
// Created by Антон on 14.04.2020.
//

#ifndef TIMES_AND_PLANES_CALCULATE_TIMES_H
#define TIMES_AND_PLANES_CALCULATE_TIMES_H

#include <Algorithmic program/Measure units/Time.h>
#include <Algorithmic program/Fields of Zone/Point.h>
#include "Algorithmic program/Zone.h"

//TODO Добавить описание
/**
 * По умолчанию, start_point = -1, то есть рассчёт происходит с самой первой точки потока с нулевым интервалом времени
 * По умолчанию, end_point = -1, то есть рассчёт происходит до точки с флагом LAND
 *
 *
 */
void
calc_TimeSegments(const Flow &flow, const std::vector<CheckPoint> &checkPoints, const std::vector<WaitingArea> &waitingAreas,
                  std::map<int, std::vector<TS>> &times, std::map<int, std::vector<std::pair<TS, int>>> &not_merged_times, int start_point = -1, int end_point = -1);

void calc_TS_edges_of_constricted_zone(Zone &zone);

TS plane_arc_Time(const CheckPoint &start, const CheckPoint &second, const PlanePoint &plane);

TS semicircle_Time(const CheckPoint &start, const CheckPoint &second);

int topID(Flow &flow, const int point_ID);

TS plane_checkPoint_Time(const PlanePoint &plane, const CheckPoint &point_there);

TS checkPoint_checkPoint_Time(const CheckPoint &point_from, const CheckPoint &point_there);

#endif //TIMES_AND_PLANES_CALCULATE_TIMES_H
