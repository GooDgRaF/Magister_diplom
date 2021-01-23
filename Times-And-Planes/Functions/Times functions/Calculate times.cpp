//
// Created by Антон on 14.04.2020.
//

#include "Calculate times.h"
#include "MergeTimes.h"
#include "Fields of Zone/Maps.h"
#include <cmath>
#include <iostream>

using namespace std;

//По умолчанию, i = -1. Во избежания результата, когда вызвали фуекцию с i = 0,
//То есть рассчёт происходит с самой первой точки потока с нулевым интервалом времени
void
calculateTimes(Flow &flow, const vector<CheckPoint> &checkPoints, const vector<StandardScheme> &standardSchemes, int i)
    {
        if (i == -1)
        {
            flow.times[flow.start_point].push_back({Time::createTsec(0),
                                                    Time::createTsec(0)}); //Выставляем начальной точке потока времена по нулям
            flow.not_merged_times[flow.start_point].push_back({Time::createTsec(0),
                                                               Time::createTsec(0)}); //Выставляем начальной точке потока времена по нулям
        i++;
        }

        while (i < flow.graph_of_descendants.size())
        {
            int j = flow.keys[i]; //Изначальый ID точки
            try
            {
                mergeTimes(flow.times[j]);
            }
            catch (runtime_error &er)
            {
                cerr << er.what() << " on " << checkPoints[j].name << endl;
                exit(-4);
            }

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

            Distance x0 = checkPoints[j].x;
            Distance y0 = checkPoints[j].y;
            Distance z0 = checkPoints[j].z;
            Velocity vmin0 = checkPoints[j].Vmin;
            Velocity vmax0 = checkPoints[j].Vmax;


            for (auto son : flow.graph_of_descendants[j])
            {

                Distance x1 = checkPoints[son].x;
                Distance y1 = checkPoints[son].y;
                Distance z1 = checkPoints[son].z;
                Velocity vmin1 = checkPoints[son].Vmin;
                Velocity vmax1 = checkPoints[son].Vmax;


                Distance S = sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2) + pow(z1 - z0, 2));  //sqt((x1-x0)^2+...)
                Time tmin = Time::createTsec(0);
                Time tmax = Time::createTsec(0);


                tmin = 2 * S / (vmax0 + vmax1);
                tmax = 2 * S / (vmin0 + vmin1);


                for (auto &time_segment : flow.times[j])
                {
                    flow.times[son].push_back({time_segment.first + tmin, time_segment.second + tmax});
                }
                for (auto &pair : flow.not_merged_times[j])
                {
                    flow.not_merged_times[son].push_back({pair.first + tmin, pair.second + tmax});
                }
            }
            i++;
        }
    }
