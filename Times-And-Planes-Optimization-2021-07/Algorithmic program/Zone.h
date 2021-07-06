//
// Created by Антон on 27.03.2020.
//

#ifndef TIMES_AND_PLANES_ZONE_H
#define TIMES_AND_PLANES_ZONE_H

#include <vector>
#include <set>
#include <algorithm>
#include <Algorithmic program/Fields of Zone/Waiting area.h>
#include "Algorithmic program/Fields of Zone/Point.h"
#include "Algorithmic program/Fields of Zone/Scheme.h"
#include "Algorithmic program/Fields of Zone/Flow.h"
#include "Algorithmic program/Measure units/MeasureUnits.h"

//using edge = std::pair<int, int>; //Ребро графа

struct edge
{
    int from;
    int there;
    
    edge(const int from, const int there) : from{from}, there{there}
        {};
    
    friend bool operator<(const edge &ed1, const edge &ed2)
        {
            return ed1.from < ed2.from;
        };
};

struct Trajectory
{
private:
    std::map<int, std::vector<TS>> trajectory;// ID в топологическом порядке  --> массив временнЫх интервалов

public:
    Trajectory(const int i, const std::vector<TS> &times) : trajectory{}
        {
            trajectory.emplace(i, times);
        };
    
    Trajectory(): trajectory{}
        {};
    
    void emplace(const int i, const std::vector<TS> &times)
        {
            trajectory.emplace(i, times);
        }
    
    void erase(const int i)
        {
            trajectory.erase(i);
        }
    
    std::vector<TS>& at(const int i)
        {
            return trajectory.at(i);
        }
};

struct Zone
{
    std::vector<CheckPoint> checkPoints;
    std::vector<Scheme> schemes;
    std::vector<WaitingArea> waitingAreas;
    std::vector<Flow> flows;
    
    std::vector<std::vector<int>> graph; //Граф зоны. Задан списками Следующий
    std::map<int, std::vector<int>> constricted_graph; //Сжатый граф зоны. Задан списками предшественников
    std::map<edge, std::vector<TS>> edge_tss; //Ребро из constricted_graph --> временные интервалы
    
    
    std::vector<StandardScheme> standardSchemes;
    
    int final_point{-1};
    
    
    void print_flows_keys();
    
    void print_key_of_flow(int number_of_flow);
    
    void print_as_string();
    
    void print_flows_as_string_des();
    
    void print_flows_as_string_anc();
    
    void print_flows_as_string_des(bool sort);
    
    void print_times();
    
    void print_not_merged_times();
    
    void print_constricted_graph_of_parents();
    
    void print_constricted_TS();
};


#endif //TIMES_AND_PLANES_ZONE_H
