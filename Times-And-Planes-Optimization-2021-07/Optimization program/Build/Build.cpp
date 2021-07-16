//
// Created by Антон on 09.07.2021.
//

#include "Build.h"
#include "Optimization program/Flow.h"
#include "Optimization program/Read/Read.h"

using namespace std;

void build_Flow(std::string_view path_PointsFile, std::string_view path_HoldingAreas, std::string_view path_SchemesFile)
{
    read_checkPoints(path_PointsFile);
    read_holding_areas(path_HoldingAreas);
    read_schemes(path_SchemesFile);
    
    build_hull_of_Flow();
    build_graph_of_Flow(0);
}

void build_hull_of_Flow()//TODO ДИСКРИМИНАЦИЯ ТРОМБОНА. За схему не считают!
{
    flow.hull.resize(flow.checkPoints.size());//Строим каркас списками Следующий
    for (const auto &scheme : flow.schemes)
    {
        assert(!scheme.path.empty()); //Пустая схема --- см как считываешь схемы!
        for (int i = 0; i < scheme.path.size() - 1; i++)
        {
            if (scheme.type != "T")
                flow.hull[scheme.path[i]].insert(scheme.path[i + 1]);
        }
    }
}

Vertex phantom(const CheckPoint &cp)
{
    Vertex v{cp.ID};
    v.name = cp.name;
    
    return v;
}

Vertex init_vertex(const int cpID, const string_view append_to_name = "")
{
    Vertex v = phantom(flow.checkPoints.at(cpID));// Создать вершину
    v.name += append_to_name;
    flow.checkPoints.at(cpID).vs.push_back(v.ID);
    flow.graph.vs.push_back(v);
    
    return v;
}

void build_graph_of_Flow(int start_point)
{
    const auto &h = flow.hull;
    auto &g = flow.graph;
    auto &cps = flow.checkPoints;
    
    if (auto it = flow.CP2HA.find(start_point);
            it != flow.CP2HA.end())
    {
        init_vertex(start_point);// На этой нет ЗО
        init_vertex(start_point, "_HA-" + to_string(it->second));// Создали вершину, на которой есть ЗО
        flow.vex2HA.insert({g.vs.back().ID, it->second}); // Запомнили в отображение
        
    }
    else
        init_vertex(start_point);
    
    int predID{start_point};
    bool isEnd{false};
    do
    {
        for (const auto &currID : h.at(predID))
        {
            if (auto itHA = flow.CP2HA.find(currID); //Если есть ЗО
                    itHA != flow.CP2HA.end())
            {
                Vertex vHA = init_vertex(currID, "_HA-" + to_string(itHA->second));// Создали вершину, на которой есть ЗО
                flow.vex2HA.insert({g.vs.back().ID, itHA->second}); // Запомнили в отображение
                Vertex v = init_vertex(currID);// Создали вершину, на которой нет ЗО
                
                v.sons.insert(vHA.ID);//От обычной к точке с ЗО.
                
                vector<int> to_insert{v.ID, vHA.ID};
                for (const auto &vID : to_insert) // Соединить предыдущие вершины и две вершины ЗО
                {
                    for (const auto &v_pred : cps.at(predID).vs)
                    {
                        g.at(v_pred).sons.insert(vID);
                    }
                }
            }
            else if (auto itSSch = flow.point_toSScheme.find(currID); itSSch != flow.point_toSScheme.end())//Точка начала спрямления
            {
                //Создать size() + 1 точек
                int schFrom_size = flow.schemes.at(itSSch->second).stFrom.size();
                auto it_stFrom = flow.schemes.at(itSSch->second).stFrom.begin();
                vector<int> vSSch_IDs{};
                for (int i = 0; i < schFrom_size + 1; ++i)
                {
                    Vertex vSSch = init_vertex(*it_stFrom, "-" + to_string(i));
                    vSSch_IDs.push_back(vSSch.ID);
                    for (const auto &v_pred : cps.at(predID).vs)
                    {
                        g.at(v_pred).sons.insert(vSSch.ID);
                    }
                }
                
                //TODO Думать ниже. От 0 до всех 1 выше.
                //Для каждой последующей точки нужно создавать на одну меньше и соединять только с нужной + добавлять ребро в отображение
                for (int i = schFrom_size; i > 1 ; --i)
                {
                    it_stFrom++;//Сдвинули на след. точку из точек возможных спрямлений
                    for (int j = 0; j < schFrom_size; ++j)
                    {
                        init_vertex(*it_stFrom,"-" + to_string(j));
                        
                    }
                
                }
            }
            else
            {
                Vertex v_curr = init_vertex(currID);
                for (const auto &v_pred : cps.at(predID).vs)
                {
                    g.at(v_pred).sons.insert(v_curr.ID);
                }
            }
            
            if (h.at(currID).empty())
                isEnd = true;
            else
                predID = currID;
        }
        
    }
    while (!isEnd);
}