//
// Created by Антон on 21.06.2021.
//

#include "Backward propagation.h"

using namespace std;

void backward_propagation(Zone &zone, int flow_ID, const TS &goal, int start_point)
    {
        if (start_point == -1)
            start_point = zone.final_point;
        
        //intersection_TS();
        //map<int, vector<pair<TS, int>>>
    }

TS intersection_TS(const TS &ab, const TS &cd)
    {
        TS zero_TS = Time::create_zero_TS();
        auto a = ab.first.getTsec(), b = ab.second.getTsec(), c = cd.first.getTsec(), d = cd.second.getTsec();
        
        if (((c < a) && (a <= d) && (d < b)))//c < a <= d < b
            return {Time::createTsec(a), Time::createTsec(d)};
        if (((a < c) && (c <= b) && (b < d)))//a < c <= b < d
            return {Time::createTsec(c), Time::createTsec(b)};
        if (((a <= c) && (c <= d) && (d <= b)))//a <= c <= d <= b
            return {Time::createTsec(c), Time::createTsec(d)};
        if (((c <= a) && (a <= b) && (b <= d))) //c <= a <= b <= d
            return {Time::createTsec(a), Time::createTsec(b)};
        return zero_TS;
    }