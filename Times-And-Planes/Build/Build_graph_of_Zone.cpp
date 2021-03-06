//
// Created by Антон on 23.03.2020.
//

#include <iostream>
#include <Functions/Geometric functions/Calculate standard scheme.h>
#include "Build_graph_of_Zone.h"
#include "Functions/Assistant functions/Find-InVector-bool.h"

using namespace std;

void Build_graph_of_Zone(Zone &zone){

		for (auto &stScheme : zone.standardSchemes)
		{
            fill_StScheme(zone.checkPoints, stScheme);
		}

		for (const auto &scheme : zone.schemes) //Строим граф списками Следующий
		{
			/*Идём до size - 1, так как мы соединяем дугами со следующими точками,
				 * то есть будет связь между предпоследней точкой и последней
				 * и так как схемы соединяются в нахлёст, то есть конец одной схемы это начало другой, то все хорошо.
				 */
			for (int i = 0; i < scheme.path.size() - 1; i++)
			{
				zone.graph_of_descendants[scheme.path[i]].push_back(scheme.path[i +	1]); //Соединить текущую точку со следующей

			}

		}

		cout << "Build graph of zone successes!" << endl;
	}