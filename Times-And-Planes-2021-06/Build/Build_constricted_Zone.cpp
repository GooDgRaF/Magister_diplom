//
// Created by Антон on 15.06.2021.
//

#include "Build_constricted_Zone.h"
#include <set>

using namespace std;

void build_constricted_Zone(Zone &zone)
    {
        vector<int> flows_start_point{};
        for (const auto &flow : zone.flows)
        {
            flows_start_point.push_back(flow.start_point);
        }
        
        
        vector<bool> is_merged{}; //Сливался ли i-ый поток
        is_merged.resize(zone.flows.size(), false);
        
        map<int, vector<int>> constricted_zone{};// ID точки --> стартовые точки потоков, которые слились в данной точке
        
        
        while ((count(is_merged.begin(), is_merged.end(), false)) >= 2)
        {
            for (const auto &flow : zone.flows)
            {
                intersection(flow, zone.flows, constricted_zone, flows_start_point);// Собираем точки в которых сливаются потоки
            }
            
            set<int> met_before{};
            for (int i = 0; i < flows_start_point.size(); ++i)
            {
                if (met_before.find(flows_start_point[i]) != met_before.end())
                {
                    met_before.insert(flows_start_point[i]);
                }
                else
                {
                    is_merged[i] = true;
                }
            }
        }
        
        zone.constricted_graph_of_parents = constricted_zone;
        
        
    }

void
intersection(const Flow &given_flow, const std::vector<Flow> &flows,
             std::map<int, std::vector<int>> &pointID_to_mergedFlows, std::vector<int> &flows_start_point)
    {
        bool is_merged = false;
        
        vector<set<int>> points_in_flows{};
        for (const auto &flow : flows)
        {
            set<int> temp{};
            for (const auto &point : flow.path)
            {
                temp.insert(point);
            }
            points_in_flows.push_back(temp);
        }
        
        for (const auto &point : given_flow.path)
        {
            if (is_merged)
            {
                break;
            }
            else
            {
                for (const auto &flow : flows)
                {
                    if ((given_flow.ID != flow.ID) //Потоки разные
                        &&
                        (points_in_flows[flow.ID].find(point) != points_in_flows[flow.ID].end())) //Точка есть в потоке
                    {
                        pointID_to_mergedFlows[point].push_back(flows_start_point[flow.ID]); //Записали к точке родителя
                        flows_start_point[given_flow.ID] = point;// Передвинули родителя
                        is_merged = true;
                    }
                }
            }
        }
    }
