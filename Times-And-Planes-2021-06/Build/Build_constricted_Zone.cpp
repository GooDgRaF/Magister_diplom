//
// Created by Антон on 15.06.2021.
//

#include "Build_constricted_Zone.h"
#include <set>
#include "Fields of Zone/Maps.h"
using namespace std;

void build_constricted_Zone(Zone &zone)
    {
        for (const auto &checkPoint : zone.checkPoints) //Запишем ВПП
        {
            if (checkPoint.landing_flag == true)
            {
                zone.final_point = checkPoint.ID;
            }
        }
        
        vector<int> flows_start_point{};
        for (const auto &flow : zone.flows)
        {
            flows_start_point.push_back(flow.start_point);
        }
        
        vector<bool> is_merged_flows{}; //Сливался ли i-ый поток
        is_merged_flows.resize(zone.flows.size(), false);
        
        map<int, vector<int>> constricted_zone{};// ID точки --> стартовые точки потоков, которые слились в данной точке
        
        //TODO сделать проверку на  met_before до цикла, то есть если сразу же на входе есть вложенные потоки
        while ((count(is_merged_flows.begin(), is_merged_flows.end(), false)) >= 2)
        {
            for (const auto &flow : zone.flows)
            {
                if (!(is_merged_flows[flow.ID]))
                {
                    flow_intersection(flow, zone.flows, constricted_zone, flows_start_point, is_merged_flows);// Собираем точки в которых сливаются потоки
                }
            }
            set<int> met_before{};//Точки в которых уже слились какие-то потоки на данном шаге
            for (int i = 0; i < flows_start_point.size(); ++i)
            {
                if (!(is_merged_flows[i]))//Если поток активный (неслитый)
                {
                    if (met_before.find(flows_start_point[i]) == met_before.end())
                    {
                        met_before.insert(flows_start_point[i]);
                    }
                    else
                    {
                        is_merged_flows[i] = true;
                    }
                }
            }
        }
        
        zone.constricted_graph = constricted_zone;
    }

void
flow_intersection(const Flow &given_flow, const std::vector<Flow> &flows, std::map<int, std::vector<int>> &pointID_to_mergedFlows, std::vector<int> &flows_start_point, const vector<bool> &mask)
    {
        bool is_merged = false;
        
        vector<set<int>> points_in_flows{};
        for (const auto &flow : flows)
        {
            if (!(mask[flow.ID]))//Рассматриваем только по одному представителю от слитых потоков
            {
                set<int> temp{};
                auto it_start = find(flow.path.begin(), flow.path.end(), flows_start_point[flow.ID]);
                for (auto it = it_start; it != flow.path.end(); it++)
                {
                    temp.insert(*it);
                }
                points_in_flows.push_back(temp);
            }
            else
            {
                points_in_flows.emplace_back();
            }
        }
        
        for (auto it_point = find(given_flow.path.begin(), given_flow.path.end(), flows_start_point[given_flow.ID]);
             it_point != given_flow.path.end(); it_point++)
        {
            if (is_merged)//Идём до первого слияния данного потока с любым другим
            {
                break;
            }
            for (const auto &flow : flows)
            {
                if (is_merged)//Идём до первого слияния данного потока с любым другим
                {
                    break;
                }
                if (!(mask[flow.ID]))
                {
                    if ((given_flow.ID != flow.ID) //Потоки разные
                        &&
                        (points_in_flows[flow.ID].find(*it_point) !=
                         points_in_flows[flow.ID].end())) //Точка есть в потоке
                    {
                        if ((*it_point ==
                             flows_start_point[given_flow.ID])) //Если точка совпала с началом, то данный поток содержится в текущем и в обработка не нужна
                        { is_merged = true; }
                        else
                        {
                            pointID_to_mergedFlows[*it_point].push_back(flows_start_point[given_flow.ID]); //Записали к точке родителя
                            flows_start_point[given_flow.ID] = *it_point;// Передвинули родителя
                            is_merged = true;
                        }
                    }
                }
            }
        }
    }
