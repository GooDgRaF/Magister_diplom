//
// Created by Антон on 14.04.2020.
//

#include "MergeTimes.h"
#include <map>

using namespace std;

void mergeTimes(vector<TS> &times)
	{
		map<Time, int, compLess> valueAction; //Значение - действие
		for (auto ts : times)
		{
			valueAction[ts.min]++;
			valueAction[ts.max]--;
		}
		
		times.clear();
		
		int sum = 0;
		auto itMap = valueAction.begin();
		Time start = itMap->first;
		for (itMap = valueAction.begin(); itMap != valueAction.end(); itMap++)
		{
			sum = sum + itMap->second;
			if (sum == 0)
			{
				times.emplace_back(start, itMap->first);
				if (itMap != valueAction.end())
				{
					itMap++;
					start = itMap->first;
					itMap--;
				}
			}
		}
		
		
	}
