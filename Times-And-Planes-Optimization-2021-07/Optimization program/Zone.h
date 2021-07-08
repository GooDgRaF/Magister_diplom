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
    std::vector <Scheme> schemes;
//    std::vector <WaitingArea> waitingAreas;
//    std::vector <Flow> flows;
    
//    std::vector <std::vector<int>> graph; //Граф зоны. Задан списками Следующий
//    std::map<int, std::vector<int>> constricted_graph; //Сжатый граф зоны. Задан списками предшественников
//    std::map <edge, std::vector<TS>> edge_tss; //Ребро из constricted_graph --> временные интервалы
//
    
//    std::vector <StandardScheme> standardSchemes;
    
    int final_point{-1};
    
    static Zone& get_instance();
private:
    Zone() = default;
};

extern Zone zone;
#endif //TIMES_AND_PLANES_OPTIMIZATION_2021_07_ZONE_H
