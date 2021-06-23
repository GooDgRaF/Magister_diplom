//
// Created by Антон on 29.03.2020.
//
#include <iostream>
#include <cmath>
#include "Zone.h"
#include "Fields of Zone/Maps.h"

using namespace std;


void Zone::print_flows_keys()
    {
        for (auto &flow : flows)
        {
            cout << flow.name << ": ";
            for (auto item : flow.path)
            {
                cout << item << "  ";
            }
            cout << endl;
        }
        cout << endl;
    }


void Zone::print_key_of_flow(int number_of_flow)
    {
        for (auto item : flows[number_of_flow].path)
        {
            cout << item << "  ";
        }
        cout << endl << endl;
        
    }


void Zone::print_as_string()
    {
        for (int i = 0; i < graph.size(); ++i)
        {
            cout << checkPoints[i].name << " --> ";
            for (auto el : graph[i])
            {
                cout << checkPoints[el].name << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

void Zone::print_flows_as_string_des()
    {
        for (auto &flow : flows)
        {
            cout << flow.name << ": " << endl;
            for (auto &vertex : flow.graph_of_descendants)
            {
                cout << checkPoints[vertex.first].name << " --> ";
                for (auto el : vertex.second)
                {
                    cout << checkPoints[el].name << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        cout << endl;
        
    }

void Zone::print_flows_as_string_des(bool sort)
    {
        if (sort == true)
        {
            cout << "SORTED" << endl;
            for (auto &flow : flows)
            {
                cout << flow.name << ": " << endl;
                for (int point_ID : flow.path)
                {
                    cout << checkPoints[point_ID].name << " --> ";
                    for (auto &el : flow.graph_of_descendants[point_ID])
                    {
                        cout << checkPoints[el].name << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
            cout << endl;
        }
        else
        {
            print_flows_as_string_des();
        }
    }

void Zone::print_flows_as_string_anc()
    {
        for (auto &flow : flows)
        {
            cout << flow.name << ": " << endl;
            for (auto &vertex : flow.graph_of_ancestors)
            {
                cout << checkPoints[vertex.first].name << " <-- ";
                for (auto el : vertex.second)
                {
                    cout << checkPoints[el].name << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        cout << endl;
        
    }

void Zone::print_times()
    {
        for (auto &flow : flows)
        {
            cout << flow.name << ": " << endl;
            for (int point_ID : flow.path)
            {
                cout << checkPoints[point_ID].name << " --> ";
                for (auto &ts : flow.times[point_ID])
                {
                    cout << "[" << ts.min << ", " << ts.max << "] ";
                }
                cout << endl;
            }
            cout << endl;
        }
        cout << endl;
    }

void Zone::print_not_merged_times()
    {
        for (auto &flow : flows)
        {
            cout << flow.name << ": " << endl;
            for (int point_ID : flow.path)
            {
                cout << checkPoints[point_ID].name << " --> ";
                for (auto &pair : flow.not_merged_times[point_ID])
                {
                    cout << "[" << pair.first << ", " << ((pair.second != -1) ? checkPoints[pair.second].name : "NO_PARENT") << "] ";
                }
                cout << endl;
            }
            cout << endl;
        }
        cout << endl;
    }

void Zone::print_constricted_graph_of_parents()
    {
        cout << "Constricted zone: " << endl;
        for (const auto &item : constricted_graph)
        {
            cout << checkPoints[item.first].name << ":";
            for (const auto &el : item.second)
            {
                cout << ' ' << checkPoints[el].name;
            }
            cout << endl;
        }
        cout << endl;
    }

void Zone::print_constricted_TS()
    {
        cout << "Constricted: edge --> TS" << endl;
        for (const auto &ed_ts : edge_ts)
        {
            cout << checkPoints[ed_ts.first.from].name << " --> " << checkPoints[ed_ts.first.there].name <<
                 " : " << ed_ts.second << endl;
        }
        cout << endl;
    }


