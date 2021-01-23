//
// Created by Антон on 14.01.2021.
//

#include <Fields of Zone/Maps.h>
#include <Functions/Geometric functions/Nearest point from the center to .h>
#include "Calculate times new plane.h"
#include "Functions/Times functions/Calculate times.h"
#include <Functions/Times functions/Initialization of time segments.h>
#include <Functions/Times functions/Calc time segments for StScheme.h>

using namespace std;

int topID(Flow &flow, const int point_ID);


/*
 Функция принимает на вход Зону, структуру типа (x,y,z,v), имя потока,
к которому отнесли данное ВС, контрольную точу куда оно летит и ещё две КТ,
образующие рербро на котором в данный моент находится ВС.
*/


int calc_plane(Zone &zone, const PlanePoint &plane)
    {
        try
        {
            pointNameToID.at(plane.destination);
            pointNameToID.at(plane.on_edge.first);
            pointNameToID.at(plane.on_edge.second);
        }
        catch (const out_of_range &ex) //Ловим ошибку о не обнаружении точки среди точек из checkPoints
        {
            cerr << "Can't find '"
                 << plane.destination << "' or '"
                 << plane.on_edge.first << "' or '"
                 << plane.on_edge.second << "' among points from Points file" << endl;
            return -1;
        }

        Flow &flow = zone.flows[flowNameToID[plane.flow_for_plane]];
        const pair<int, int> edge_ID_ID = {pointNameToID[plane.on_edge.first],
                                           pointNameToID[plane.on_edge.second]};

        if (edgeTo_stScheme_part.find(edge_ID_ID) !=
            edgeTo_stScheme_part.end())//Если ВС на стандартной схеме
        {
            calc_and_initStScheme(flow, zone.checkPoints, plane, edge_ID_ID);//Обработка ст. схемы
            calculateTimes(flow, //Рассчитываем все времена, которые "ниже по течению" начала ст. схемы
                           zone.checkPoints, zone.standardSchemes,
                           topID(flow, edgeTo_stScheme_part[edge_ID_ID].first.start_ID));
            zone.flows[0].print_times();//Сливаем куда-то
            flow.times.clear();
            return 0;
        }
        else
        {
            const int ID_there = pointNameToID[plane.destination];//Записываем ID точки "куда"
            initialTimes(flow, zone.checkPoints, plane, edge_ID_ID, ID_there);//Записали временные интервалы          
            calculateTimes(flow, zone.checkPoints, zone.standardSchemes, topID(flow, ID_there));//Рассчитываем все времена, которые "ниже по течению"
            zone.flows[0].print_times();//Сливаем куда-то
            flow.times.clear();
            return 0;
        }
    }


int topID(Flow &flow, const int point_ID)
    {
        auto it_index_there = find(flow.keys.begin(), flow.keys.end(), point_ID);
        const int top_ID_there = it_index_there - flow.keys.begin();
        return top_ID_there;
    }
