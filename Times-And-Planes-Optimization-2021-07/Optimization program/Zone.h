//
// Created by Антон on 07.07.2021.
//

#ifndef TIMES_AND_PLANES_OPTIMIZATION_2021_07_ZONE_H
#define TIMES_AND_PLANES_OPTIMIZATION_2021_07_ZONE_H
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <Optimization program/Fields of Zone/Fields of Zone.h>

class CheckPoint;

struct Zone
{
    std::vector<CheckPoint> checkPoints{};
    std::map<std::string, int> pointName_to_ID{};
    
    std::vector<Scheme> schemes{};
    std::map<int, std::set<int>> point_to_strFrom{};
    
    std::vector <HoldingArea> holdingAreas{};
    std::map<int, int> point_to_holdingArea{};
//    std::vector <Flow> flows;
    
    std::vector<std::set<int>> graph{}; //Граф зоны. Задан списком потомков
    std::vector<std::set<int>> ancestors_graph{}; //Граф зоны. Задан списком предшественников. Спрямления являются рёбрами графа
//    std::map<int, std::vector<int>> constricted_graph; //Сжатый граф зоны. Задан списками предшественников
//    std::map <edge, std::vector<TS>> edge_tss; //Ребро из constricted_graph --> временные интервалы
//
    
    std::map<int, int> trj; // Точка --> потомок
    std::vector<std::map<int, int>> trjs;
    
    int final_point{-1};
    
    static Zone& get_instance();
private:
    Zone() = default;
};
extern Zone zone;

void print_Zone();

void
calc_best_trajectory(std::vector<std::map<int, int>> &trjs, const int point_to_reach, const int current_point);
#endif //TIMES_AND_PLANES_OPTIMIZATION_2021_07_ZONE_H
