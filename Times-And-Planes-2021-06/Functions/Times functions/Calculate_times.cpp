//
// Created by Антон on 14.04.2020.
//

#include "Calculate_times.h"
#include "MergeTimes.h"
#include "Fields of Zone/Maps.h"
#include "Time segment from point to checkPoint.h"
#include <cmath>
#include <iostream>
#include "Plane enum.h"

using namespace std;

//По умолчанию, i = -1. Во избежания коллизии, когда вызвали функцию с i = 0,
//То есть рассчёт происходит с самой первой точки потока с нулевым интервалом времени
void
calc_TimeSegments(Flow &flow, const vector<CheckPoint> &checkPoints, const vector<StandardScheme> &standardSchemes, int i)
    {
        if (i == -1) //Рассчёт происходит с самой первой точки потока с нулевым интервалом времени
        {
            flow.times[flow.start_point].push_back({Time::createTsec(0),
                                                    Time::createTsec(0)}); //Выставляем начальной точке потока времена по нулям
            flow.not_merged_times[flow.start_point].push_back({{Time::createTsec(0),
                                                                Time::createTsec(0)}, NO_PARENT});
            i++;
        }
        
        while (i < flow.graph_of_descendants.size()) // до конца графа
        {
            int current_point = flow.keys[i]; //Изначальый ID точки
            
            
            if (checkPointIDtoStSchemeID.count(current_point) != 0) //Если точка является началом стандартной схемы
            {
                int scheme_ID = checkPointIDtoStSchemeID.at(current_point);
                
                for (auto const &time_segment : flow.times.at(current_point))
                {
                    for (int m = 1; m <= standardSchemes.at(scheme_ID).repeat; m++)
                    {
                        pair<Time, Time> ts_m = {time_segment + m*standardSchemes[scheme_ID].ts};
                        flow.times[current_point].push_back(ts_m);
                    }
                }
                for (auto const &pair_ts_parent : flow.not_merged_times.at(current_point))
                {
                    for (int m = 1; m <= standardSchemes[scheme_ID].repeat; ++m)
                    {
                        pair<Time, Time> ts_m = {pair_ts_parent.first + m*standardSchemes[scheme_ID].ts};
                        flow.not_merged_times[current_point].push_back({ts_m, pair_ts_parent.second});
                    }
                }
            }
            
            for (auto const son : flow.graph_of_descendants[current_point]) //Заполняем времена линейных участков
            {
                pair<Time, Time> son_time = checkPoint_checkPoint_Time(checkPoints[current_point], checkPoints[son]);
                pair<int, int> edge_ID_ID = {current_point, son};
                if (edgeTo_ends_str_ID.find(edge_ID_ID) != edgeTo_ends_str_ID.end()) // участок спрямления
                {
                    for (auto const &str_point : edgeTo_ends_str_ID[edge_ID_ID]) // для всех точек спрямления
                    {
                        pair<Time, Time> str_time = {
                                checkPoint_checkPoint_Time(checkPoints[current_point], checkPoints[str_point]).first //мин время - по кратчайшей наибыстрейше
                                , //макс время - через точку из path самым медленным способом
                                son_time.second +
                                checkPoint_checkPoint_Time(checkPoints[son], checkPoints[str_point]).second};
                        
                        for (auto const &time_segment : flow.times[current_point])
                        {
                            flow.times[str_point].push_back({time_segment + str_time});
                        }
                        for (auto const &pair_ts_parent : flow.not_merged_times[current_point])
                        {
                            flow.not_merged_times[str_point].push_back({pair_ts_parent.first + str_time,
                                                                        current_point});
                        }
                        
                    }
                }
                
                
                for (auto const &time_segment : flow.times[current_point])
                {
                    flow.times[son].push_back(time_segment + son_time);
                }
                for (auto const &pair_ts_parent : flow.not_merged_times[current_point])
                {
                    flow.not_merged_times[son].push_back({pair_ts_parent.first + son_time, current_point});
                }
            }
            try
            {
                mergeTimes(flow.times[current_point]);
            }
            catch (runtime_error &er)
            {
                cerr << er.what() << " on " << checkPoints[current_point].name << endl;
                exit(-4);
            }
            i++;
        }
    }
