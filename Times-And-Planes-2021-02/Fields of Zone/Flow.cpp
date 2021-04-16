//
// Created by Антон on 15.01.2021.
//
#include "Fields of Zone/Flow.h"

using namespace std;

void Flow::print_times()
    {
        for (int key : keys)
        {
            cout << key << " --> ";
            for (const auto &time_segment : times[key])
            {
                cout << time_segment;
            }
            cout << endl;
        }
        cout << endl;
    }
