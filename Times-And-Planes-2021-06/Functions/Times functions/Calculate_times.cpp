//
// Created by Антон on 14.04.2020.
//

#include <Functions/Geometric functions/Distance between two Points.h>
#include <Functions/Geometric functions/Arc length.h>
#include "Calculate_times.h"
#include "MergeTimes.h"
#include "Fields of Zone/Maps.h"
#include <iostream>
#include "Plane enum.h"
#include "cassert"

using namespace std;

void
calc_TimeSegments(const Flow &flow, const std::vector<CheckPoint> &checkPoints, const std::vector<WaitingArea> &waitingAreas,
                  std::map<int, std::vector<TS>> &times, std::map<int, std::vector<std::pair<TS, int>>> &not_merged_times,
                  int start_point, int end_point)
    {
        auto it_current_point = flow.path.cbegin();
        if (start_point == -1)
        {
            times[flow.start_point].push_back({0, 0}); //Выставляем начальной точке потока времена по нулям
            not_merged_times[flow.start_point].push_back({{0, 0}, NO_PARENT});
        }
        else
        {
            auto it = find(flow.path.begin(), flow.path.end(), start_point);
            assert(it != flow.path.end() && "'start_point' does not belong flow");
            it_current_point = it;
            
            if (times.empty()) //Если нет начальных интервалов, то выставить по нулям
            {
                times[*it_current_point].push_back({0, 0});
                not_merged_times[*it_current_point].push_back({{0, 0}, NO_PARENT});
            }
        }
        
        if (end_point != -1)
        {
            assert(flow.points.find(end_point) != flow.points.end()
                   && "The 'end point' does not belong to the flow");
        }
        
        assert(it_current_point <= find(flow.path.begin(), flow.path.end(), end_point)
               && "'end_point' appears before 'start_point'!");
        
        try //Слить времена в начале
        {
            mergeTimes(times.at(*it_current_point));
        }
        catch (out_of_range &er)
        {
            cerr << "No key: " << *it_current_point << " in times" << endl;
        }
        
        while ((*it_current_point != end_point)
               &&
               checkPoints[*it_current_point].landing_flag != true)
        {
            if (checkPointID_to_waID.count(*it_current_point) != 0) //Если точка является точкой входа на ЗО
            {
                int waiting_areaID = checkPointID_to_waID.at(*it_current_point);
                for (const auto &ts : times.at(*it_current_point))
                {
                    times[*it_current_point].emplace_back(ts + waitingAreas[waiting_areaID].ts_min_max);
                }
                for (const auto &[ts, parent] : not_merged_times.at(*it_current_point))
                {
                    not_merged_times[*it_current_point].emplace_back(
                            ts + waitingAreas[waiting_areaID].ts_min_max, parent);
                }
                try //Слить времена после зоны ожидания
                {
                    mergeTimes(times.at(*it_current_point));
                }
                catch (out_of_range &er)
                {
                    cerr << "No key: " << *it_current_point << " in times" << endl;
                }
            }
            
            for (auto const son : flow.graph_of_descendants.at(*it_current_point)) //Заполняем времена линейных участков
            {
                TS son_time = checkPoint_checkPoint_Time(checkPoints[*it_current_point], checkPoints[son]);
                edge cur_son = {*it_current_point, son};
                if (edgeTo_strEnds.find(cur_son) != edgeTo_strEnds.end()) // участок спрямления
                {
                    for (auto const &str_point : edgeTo_strEnds[cur_son]) // для всех точек спрямления
                    {
                        TS str_time = {
                                checkPoint_checkPoint_Time(checkPoints[*it_current_point], checkPoints[str_point]).min //мин время - по кратчайшей наибыстрейше
                                , //макс время - через точку из path самым медленным способом
                                son_time.max +
                                checkPoint_checkPoint_Time(checkPoints[son], checkPoints[str_point]).max};
                        
                        for (auto const &time_segment : times[*it_current_point])
                        {
                            times[str_point].push_back({time_segment + str_time});
                        }
                        for (auto const &[ts, parent] : not_merged_times[*it_current_point])
                        {
                            not_merged_times[str_point].push_back({ts + str_time, *it_current_point});
                        }
                    }
                }
                
                
                for (auto const &time_segment : times[*it_current_point])
                {
                    times[son].push_back(time_segment + son_time);
                }
                for (auto const &[ts, parent] : not_merged_times[*it_current_point])
                {
                    not_merged_times[son].push_back({ts + son_time, *it_current_point});
                }
            }
            it_current_point++;
            
            
            try //Слить времена в следующей точке
            {
                mergeTimes(times.at(*it_current_point));
            }
            catch (out_of_range &er)
            {
                cerr << "No key: " << *it_current_point << " in times" << endl;
            }
            
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
        for (const auto &[son, parents] : zone.constricted_graph)
        {
            for (const auto &parent : parents)
            {
                map<int, vector<TS>> times{};
                map<int, vector<std::pair<TS, int>>> unused;
                int id = find_flowID(zone.flows, parent);
                calc_TimeSegments(zone.flows[id], zone.checkPoints, zone.waitingAreas,
                                  times, unused, parent, son);
                
                zone.edge_tss.emplace(edge(parent, son), times[son]);
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