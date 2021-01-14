//
// Created by Антон on 14.04.2020.
//

#include "Calculate times.h"
#include "Functions/MergeTimes.h"
#include "Fields of Zone/Maps.h"
#include <cmath>
#include <iostream>

void calculateTimes(Zone &zone, Flow &flow)
    {
        int i = 0;
        while (i < flow.graph_of_descendants.size())
        {
            int j = flow.keys[i]; //Изначальый ID точки
            try
            {
                mergeTimes(flow.times[j]);
            }
            catch (runtime_error &er)
            {
                cerr << er.what() << " on " << zone.checkPoints[j].name << endl;
                exit(-4);
            }

            if (startPointIDtoStSchemeID.count(j) != 0) //Если точка является началом стандартной схемы
            {
                int k, m, size = flow.times[j].size(), scheme_ind = startPointIDtoStSchemeID[j];
                for (k = 0; k < size; k++)
                {
                    pair<Time, Time> &time_segment = flow.times[j][k];
                    for (m = 1; m <= zone.standardSchemes[scheme_ind].repeat; m++)
                    {
                        Time a = time_segment.first + m * zone.standardSchemes[scheme_ind].Tmin;
                        Time b = time_segment.second + m * zone.standardSchemes[scheme_ind].Tmax;
                        flow.times[j].push_back({a, b});
                        flow.not_merged_times[j].push_back({a,b});
                    }
                }
            }

            Coordinate x0 = zone.checkPoints[j].x;
            Coordinate y0 = zone.checkPoints[j].y;
            Coordinate z0 = zone.checkPoints[j].z;
            Velocity vmin0 = zone.checkPoints[j].Vmin;
            Velocity vmax0 = zone.checkPoints[j].Vmax;


            for (auto son : flow.graph_of_descendants[j])
            {

                Coordinate x1 = zone.checkPoints[son].x;
                Coordinate y1 = zone.checkPoints[son].y;
                Coordinate z1 = zone.checkPoints[son].z;
                Velocity vmin1 = zone.checkPoints[son].Vmin;
                Velocity vmax1 = zone.checkPoints[son].Vmax;


                Coordinate S = sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2) + pow(z1 - z0, 2));  //sqt((x1-x0)^2+...)
                Time tmin = Time::createTsec(0);
                Time tmax = Time::createTsec(0);


                tmin = 2 * S / (vmax0 + vmax1);
                tmax = 2 * S / (vmin0 + vmin1);


                for (auto &pair : flow.times[j])
                {
                    flow.times[son].push_back({pair.first + tmin, pair.second + tmax});
                }
                for (auto &pair : flow.not_merged_times[j])
                {
                    flow.not_merged_times[son].push_back({pair.first + tmin, pair.second + tmax});
                }
            }
            i++;

        }
    }
