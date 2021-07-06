//
// Created by Антон on 28.03.2020.
//

#include <stack>
#include <iostream>
#include "Algorithmic program/Fields of Zone/Maps.h"
#include "Algorithmic program/Zone.h"

using namespace std;

void Build_Flow(Zone &zone, Flow &flow)
	{
		int start_of_flow = flow.start_point;
		
		stack<int> st;
		st.push(start_of_flow);
		vector<bool> mark(zone.graph.size(), false);
		
		while (!st.empty())
		{
			int v = st.top();
			st.pop();
			
			for (int son : zone.graph[v])
			{
				flow.graph_of_descendants[v].push_back(son);
				if (!mark[son]) //Если сын ещё не посещён
				{
					st.push(son);
					mark[son] = true;
				}
			}
			
		}
		
		for (auto &[parent, sons] : flow.graph_of_descendants) //Собираем граф списками Предшественник
		{
            for (auto son : sons)
            {
                flow.graph_of_ancestors[son].push_back(parent);
                if (pointTo_strStarts.find(son) != pointTo_strStarts.end())
                {
                    for (const auto &strStart : pointTo_strStarts.at(son))
                    {
                        if (parent != strStart)//Родителя уже добавили
                        {
                            flow.graph_of_ancestors[son].push_back(strStart);
                        }
                    }
                }
            }
		}
		
		flow.points.insert(flow.start_point); //Собираем точки потока
		for (const auto &id_v: flow.graph_of_descendants)
        {
		    for (const auto son : id_v.second)
            {
		        flow.points.insert(son);
            }
        }
	}