//
// Created by Антон on 09.07.2021.
//

#include "Build.h"
#include "Optimization program/Zone.h"
#include "Optimization program/Read/Read.h"

using namespace std;

void fill_Zone(std::string_view path_PointsFile, std::string_view path_HoldingAreas, std::string_view path_SchemesFile)
    {
        read_checkPoints(path_PointsFile);
        read_holding_areas(path_HoldingAreas);
        read_schemes(path_SchemesFile);
        
        build_graph_of_Zone();
        
    }

void build_graph_of_Zone()
    {
        zone.graph.resize(zone.checkPoints.size());//Строим граф списками Следующий
        for (const auto &scheme : zone.schemes)
        {
            assert(!scheme.path.empty()); //Пустая схема --- см как считываешь схемы!
            for (int i = 0; i < scheme.path.size() - 1; i++)
            {
                zone.graph[scheme.path[i]].insert(scheme.path[i + 1]);
            }
        }
        
        zone.ancestors_graph.resize(zone.checkPoints.size()); //Строим граф списками Предок с учётом спрямлений
        for (const auto &scheme : zone.schemes)
        {
            for (int i = scheme.path.size() - 1; i > 0; --i)
            {
                zone.ancestors_graph[scheme.path[i]].insert(scheme.path[i - 1]);
                if (zone.point_to_strFrom.find(scheme.path[i]) != zone.point_to_strFrom.end())
                {
                    for (const auto &parent : zone.point_to_strFrom.at(scheme.path[i]))
                    {
                        zone.ancestors_graph[scheme.path[i]].insert(parent);
                    }
                }
            }
        }
        
        set<int> sons{};
        set<int> parents{};
        vector<pair<int, int>> to_insert{};// Запомнить пару Копия_Точки и ID ЗО
        
        for (const auto[pointID, hA_ID] : zone.point_to_holdingArea)
        {
            auto replica = zone.checkPoints[pointID];
            replica.name += "_hA";
            replica.ID = zone.checkPoints.size(); //TODO generateID?
            zone.checkPoints.push_back(replica);
            
            to_insert.emplace_back(replica.ID, hA_ID);
            sons = zone.graph[pointID];
            parents = zone.ancestors_graph[pointID];
            
        }
        
        zone.point_to_holdingArea.clear();
        for (const auto &[point, hA] : to_insert)
        {
            zone.point_to_holdingArea.insert({point, hA});
            zone.graph.push_back(sons);
            zone.ancestors_graph.push_back(parents);
            
            for (const auto &parent : parents)
                zone.graph[parent].insert(point);
            for (const auto &son : sons)
                zone.ancestors_graph[son].insert(point);
        }
    }
