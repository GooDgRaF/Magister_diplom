//
// Created by Антон on 07.07.2021.
//

#ifndef TIMES_AND_PLANES_OPTIMIZATION_2021_07_FLOW_H
#define TIMES_AND_PLANES_OPTIMIZATION_2021_07_FLOW_H

#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <Optimization program/Fields of Zone/Fields of Flow.h>
#include "Optimization program/Fields of Zone/Graph.h"

class CheckPoint;

struct Flow
{
    std::vector<CheckPoint> checkPoints{};
    std::map<std::string, int> pointName_to_ID{};
    
    Graph graph{};
    
    std::vector<Scheme> schemes{};
    std::map<int, int> point_toSScheme{};
    
    std::vector<HoldingArea> holdingAreas{};
    std::map<int, int> CP2HA{};//CP - check point, HA - Holding Area ID
    std::map<int, int> vex2HA{};//vex - vertex
    
    
    std::vector<std::set<int>> hull{}; //Каркас графа потока. Задан списком потомков
    
    std::map<int, int> best_trj; // Вершина --> потомок
    std::vector<std::map<int, int>> trjs;
    
    int final_point{-1};
    
    static Flow &get_instance();
private:
    Flow() = default;
};

extern Flow flow;

void calc_best_trajectory(std::vector<std::map<int, int>> &trjs, const int current_vertex, const int vertex_to_reach);
bool isBetter(const std::map<int, int> &trj, int start_vertex, int end_vertex, double t0, double v0, double tEnd);

void print_hull();
void print_graph();

#endif //TIMES_AND_PLANES_OPTIMIZATION_2021_07_FLOW_H
