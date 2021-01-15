//
// Created by Антон on 15.01.2021.
//
#include "Fields of Zone/Flow.h"


void Flow::print_times()
    {
        for (int key : keys)
        {
            cout << key << " --> ";
            for (auto &pair : times[key])
            {
                cout << "[" << pair.first << ", " << pair.second << "] ";
            }
            cout << endl;
        }
        cout << endl;
    }
