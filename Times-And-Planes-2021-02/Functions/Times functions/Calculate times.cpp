//
// Created by Антон on 14.04.2020.
//

#include "Calculate times.h"
#include "MergeTimes.h"
#include "Fields of Zone/Maps.h"
#include "Time segment from point to checkPoint.h"
#include <cmath>
#include <iostream>

using namespace std;

//По умолчанию, i = -1. Во избежания коллизии, когда вызвали функцию с i = 0,
//То есть рассчёт происходит с самой первой точки потока с нулевым интервалом времени
void
calculateTimes(Flow &flow, const vector<CheckPoint> &checkPoints, const vector<StandardScheme> &standardSchemes, int i)
    {
        flow.not_merged_times = flow.times; // инициализировали не слитые промежутки

        if (i == -1) //Рассчёт происходит с самой первой точки потока с нулевым интервалом времени
        {
            flow.times[flow.start_point].push_back({Time::createTsec(0),
                                                    Time::createTsec(0)}); //Выставляем начальной точке потока времена по нулям
            flow.not_merged_times[flow.start_point].push_back({Time::createTsec(0),
                                                               Time::createTsec(0)}); //Выставляем начальной точке потока времена по нулям
            i++;
        }

        while (i < flow.graph_of_descendants.size()) // до конца графа
        {
            int j = flow.keys[i]; //Изначальый ID точки


            if (checkPointIDtoStSchemeID.count(j) != 0) //Если точка является началом стандартной схемы
            {
                int k, m, size = flow.times[j].size(), scheme_ind = checkPointIDtoStSchemeID[j];
                for (k = 0; k < size; k++)
                {
                    pair<Time, Time> &time_segment = flow.times[j][k];
                    for (m = 1; m <= standardSchemes[scheme_ind].repeat; m++)
                    {
                        Time a = time_segment.first + m * standardSchemes[scheme_ind].Tmin;
                        Time b = time_segment.second + m * standardSchemes[scheme_ind].Tmax;
                        flow.times[j].push_back({a, b});
                        flow.not_merged_times[j].push_back({a, b});
                    }
                }
            }


            for (auto const son : flow.graph_of_descendants[j]) //Заполняем времена линейных участков
            {
                pair<Time, Time> son_time = checkPoint_checkPoint_Time(checkPoints[j], checkPoints[son]);
                pair<int, int> edge_ID_ID = {j, son};
                if (edgeTo_ends_str_ID.find(edge_ID_ID) != edgeTo_ends_str_ID.end()) // участок спрямления
                {
                    for (auto const &str_point : edgeTo_ends_str_ID[edge_ID_ID]) // для всех точек спрямления
                    {
                        pair<Time, Time> str_time = {
                                checkPoint_checkPoint_Time(checkPoints[j], checkPoints[str_point]).first //мин время - по кратчайшей наибыстрейше
                                , //макс время - через точку из path самым медленным способом
                                son_time.second +
                                checkPoint_checkPoint_Time(checkPoints[son], checkPoints[str_point]).second};
                        flow.times[str_point].push_back(str_time);
                        flow.not_merged_times[str_point].push_back(str_time);
                    }
                }


                for (auto const &time_segment : flow.times[j])
                {
                    flow.times[son].push_back({time_segment.first + son_time.first,
                                               time_segment.second + son_time.second});
                }
                for (auto const &time_segment : flow.not_merged_times[j])
                {
                    flow.not_merged_times[son].push_back({time_segment.first + son_time.first, time_segment.second + son_time.second});
                }
            }
            try
            {
                mergeTimes(flow.times[j]);
            }
            catch (runtime_error &er)
            {
                cerr << er.what() << " on " << checkPoints[j].name << endl;
                exit(-4);
            }

            i++;
        }
    }
