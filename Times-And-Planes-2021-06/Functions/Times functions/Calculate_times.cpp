//
// Created by Антон on 14.04.2020.
//

#include <Functions/Geometric functions/Arc length.h>
#include "Calculate_times.h"
#include "MergeTimes.h"
#include "Fields of Zone/Maps.h"
#include "Time segment from point to checkPoint.h"
#include <iostream>
#include "Plane enum.h"
#include "cassert"

using namespace std;


//По умолчанию, start_point = -1, то есть рассчёт происходит с самой первой точки потока с нулевым интервалом времени
//По умолчанию, end_point = -1, то есть рассчёт происходит до точки с флагом LAND
void
calc_TimeSegments(Flow &flow, const vector<CheckPoint> &checkPoints,
                  const vector<StandardScheme> &standardSchemes, int start_point, int end_point)
    {
        if (end_point != -1)
        {
            assert(find(flow.path.begin(), flow.path.end(), end_point) != flow.path.end() &&
                   "'end_point' does not belong flow");
        }
        
        auto it_current_point = flow.path.cbegin();
        if (start_point == -1)
        {
            flow.times[flow.start_point].push_back(Time::create_zero_TS()); //Выставляем начальной точке потока времена по нулям
            flow.not_merged_times[flow.start_point].push_back({Time::create_zero_TS(), NO_PARENT});
        }
        else
        {
            auto it = find(flow.path.begin(), flow.path.end(), start_point);
            assert(it != flow.path.end() && "'start_point' does not belong flow");
            it_current_point = it;
            
            if (flow.times.empty()) //Если нет начальных интервалов, то выставить по нулям
            {
                flow.times[*it_current_point].push_back(Time::create_zero_TS());
                flow.not_merged_times[*it_current_point].push_back({Time::create_zero_TS(), NO_PARENT});
            }
        }
        
        assert(it_current_point <= find(flow.path.begin(), flow.path.end(), end_point)
               && "'end_point' appears before 'start_point'!");
        
        while ((*it_current_point != end_point)
               &&
               checkPoints[*it_current_point].landing_flag != true)
        {
            if (checkPointIDtoStSchemeID.count(*it_current_point) != 0) //Если точка является началом стандартной схемы
            {
                int scheme_ID = checkPointIDtoStSchemeID.at(*it_current_point);
                
                for (auto const &time_segment : flow.times.at(*it_current_point))
                {
                    for (int m = 1; m <= standardSchemes.at(scheme_ID).repeat; m++)
                    {
                        pair<Time, Time> ts_m = {time_segment + m*standardSchemes[scheme_ID].ts};
                        flow.times[*it_current_point].push_back(ts_m);
                    }
                }
                for (auto const &pair_ts_parent : flow.not_merged_times.at(*it_current_point))
                {
                    for (int m = 1; m <= standardSchemes[scheme_ID].repeat; ++m)
                    {
                        pair<Time, Time> ts_m = {pair_ts_parent.first + m*standardSchemes[scheme_ID].ts};
                        flow.not_merged_times[*it_current_point].push_back({ts_m, pair_ts_parent.second});
                    }
                }
            }
            
            for (auto const son : flow.graph_of_descendants[*it_current_point]) //Заполняем времена линейных участков
            {
                pair<Time, Time> son_time = checkPoint_checkPoint_Time(checkPoints[*it_current_point], checkPoints[son]);
                pair<int, int> edge_ID_ID = {*it_current_point, son};
                if (edgeTo_ends_str_ID.find(edge_ID_ID) != edgeTo_ends_str_ID.end()) // участок спрямления
                {
                    for (auto const &str_point : edgeTo_ends_str_ID[edge_ID_ID]) // для всех точек спрямления
                    {
                        pair<Time, Time> str_time = {
                                checkPoint_checkPoint_Time(checkPoints[*it_current_point], checkPoints[str_point]).first //мин время - по кратчайшей наибыстрейше
                                , //макс время - через точку из path самым медленным способом
                                son_time.second +
                                checkPoint_checkPoint_Time(checkPoints[son], checkPoints[str_point]).second};
                        
                        for (auto const &time_segment : flow.times[*it_current_point])
                        {
                            flow.times[str_point].push_back({time_segment + str_time});
                        }
                        for (auto const &pair_ts_parent : flow.not_merged_times[*it_current_point])
                        {
                            flow.not_merged_times[str_point].push_back({pair_ts_parent.first + str_time,
                                                                        *it_current_point});
                        }
                        
                    }
                }
                
                
                for (auto const &time_segment : flow.times[*it_current_point])
                {
                    flow.times[son].push_back(time_segment + son_time);
                }
                for (auto const &pair_ts_parent : flow.not_merged_times[*it_current_point])
                {
                    flow.not_merged_times[son].push_back({pair_ts_parent.first + son_time, *it_current_point});
                }
            }
            try
            {
                mergeTimes(flow.times.at(*it_current_point));
            }
            catch (runtime_error &er)
            {
                cerr << er.what() << " on " << checkPoints[*it_current_point].name << endl;
                exit(-4);
            }
            catch (out_of_range &er)
            {
                cerr << "No key: " << *it_current_point << " in flow.times" << endl;
            }
            it_current_point++;
        }
    }


int find_flowID(const vector<Flow> &flows, int point)
    {
        for (const auto &flow : flows)
        {
            if (flow.points.find(point) != flow.points.end())
                return flow.ID;
        }
        return -1;
    }

void calc_TS_edges_of_constricted_zone(Zone &zone)
    {
        for (const auto &son_parent : zone.constricted_graph)
        {
            for (const auto &parent : son_parent.second)
            {
                int flowID = find_flowID(zone.flows, parent);
                calc_TimeSegments(zone.flows[flowID],
                                  zone.checkPoints, zone.standardSchemes, parent, son_parent.first);
                zone.constricted_ts.emplace(make_pair(parent, son_parent.first), zone.flows[flowID].times[son_parent.first].at(0)); //TODO А почему у точки слияния один интервал времени?
                zone.flows[flowID].times.clear();
                zone.flows[flowID].not_merged_times.clear();
            }
        }
        
    }


int topID(Flow &flow, const int point_ID)
    {
        auto it_index_there = find(flow.path.begin(), flow.path.end(), point_ID);
        const int top_ID_there = it_index_there - flow.path.begin();
        return top_ID_there;
    }

TS plane_arc_Time(const CheckPoint &start, const CheckPoint &second, const PlanePoint &plane)
    {
        Distance arc = arc_length(start, second, plane);
        
        Time T_initial_min = 2*arc/(plane.V + second.Vmax);
        Time T_initial_max = 2*arc/(plane.V + second.Vmin);
        
        return {T_initial_min, T_initial_max};
    }

TS semicircle_Time(const CheckPoint &start, const CheckPoint &second)
    {
        Distance semicircle = arc_length(start, second, start);
        Time T_min = 2*semicircle/(start.Vmax + second.Vmax);
        Time T_max = 2*semicircle/(start.Vmin + second.Vmin);
        
        
        return {T_min, T_max};
    }