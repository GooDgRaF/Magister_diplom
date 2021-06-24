//
// Created by Антон on 21.06.2021.
//

#include "Backward propagation.h"
#include "cassert"

using namespace std;

void backward_propagation(Zone &zone, int flow_ID, const TS &goal_ts, int start_point, int stop_backward_point)
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
        
        
        
        
    }

