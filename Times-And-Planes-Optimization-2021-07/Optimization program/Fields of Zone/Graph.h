//
// Created by Антон on 16.07.2021.
//

#ifndef TIMES_AND_PLANES_OPTIMIZATION_2021_07_GRAPH_H
#define TIMES_AND_PLANES_OPTIMIZATION_2021_07_GRAPH_H


#include <string>
#include <vector>
#include <set>
#include <map>
#include "Optimization program/Measure units/Measure units.h"
#include "cmath"

struct Vertex
{
    int ID;
    int cpID;
    std::set<int> sons; // Множество Vertex.ID
    
    std::string name;// Для отладки
    
    Vertex(const int cpID): cpID{cpID}, sons{}, name{}
    {
        ID = genID();
    }
private:
    static int genID();
    static int id;
};

class Graph
{
public:
    std::vector<Vertex> vs{}; //Массив вершин
    std::map<std::pair<int,int>, std::vector<int>> str{}; //Информация о рёбрах спрямлений
};

#endif //TIMES_AND_PLANES_OPTIMIZATION_2021_07_GRAPH_H
