//
// Created by Антон on 21.06.2021.
//

#include "Backward propagation.h"
#include "cassert"
#include "stack"
#include "Calculate_times.h"
#include "Algorithmic program/Fields of Zone/Maps.h"
using namespace std;



Trajectory
DFS(const vector<CheckPoint> &checkPoints, const Flow &flow, const int stop_backward_point, Trajectory &best_trj, Trajectory &trj, int current_point)
    {
        if (current_point == stop_backward_point)
        {
            return trj;
        }
        else
        {
            for (const auto &parent : flow.graph_of_ancestors.at(current_point))
            {
                //TODO Научиться переходить к точкам из спрямления
                
                // 1) Расширить временной интервал данной точки к предку
                TS son_parent_ts = checkPoint_checkPoint_Time(checkPoints[current_point], checkPoints[parent]);
                for (const auto &cur_ts : trj.at(current_point))
                {
                    auto bigger_sp_ts = cur_ts + TS(-son_parent_ts.max, -son_parent_ts.min); //sp = son_parent
                    //2) Пересечь полученный расширенный интервал с имеющимеся временами у предка
                    auto intrs_times_parent = intersection_vTS({bigger_sp_ts}, flow.times.at(parent));
                    //3) Записать в траекторию: Предок --> времена из 2)
                    trj.emplace(parent, intrs_times_parent);
            
            
                    auto trj_to_estimate = DFS(checkPoints, flow, stop_backward_point, best_trj, trj, parent);
                    //estimate_Trajectory(trj_to_estimate);
                    best_trj = trj_to_estimate;
                    trj.erase(parent);
                    
                }
            }
        }
        return best_trj;
    }

Trajectory backward_propagation(Zone &zone,
                                int flow_ID, const Time &goal,
                                int start_point, int stop_backward_point)
    {
        auto &flow = zone.flows[flow_ID];
        if (start_point == -1)
            start_point = zone.final_point;
        else
            assert(flow.points.find(start_point) != flow.points.end()
                   && "The 'start point' of the backward propagation does not belong to the flow");
        if (stop_backward_point == -1)
            stop_backward_point = flow.start_point;
        else
            assert(flow.points.find(stop_backward_point) != flow.points.end()
                   && "The 'stop backward point' of the backward propagation does not belong to the flow");
        Trajectory trj{start_point, {TS(goal, goal)}}, best_trj{};
        DFS(zone.checkPoints, flow, stop_backward_point, best_trj, trj, start_point);
     
        return best_trj;
    }



