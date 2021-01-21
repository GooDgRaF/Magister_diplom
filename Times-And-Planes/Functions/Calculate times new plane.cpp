//
// Created by Антон on 14.01.2021.
//

#include <Fields of Zone/Maps.h>
#include <Functions/Geometric functions/Nearest point from the center to .h>
#include "Calculate times new plane.h"
#include "Functions/Times functions/Calculate times.h"
#include <Functions/Geometric functions/Arc length.h>
#include <Functions/Times functions/Initialization of time segments.h>
#include <Functions/Times functions/Arc time.h>
#include <Functions/Times functions/Time segment from point to checkPoint.h>


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
        const int ID_there = pointNameToID[plane.destination];//Записываем начальное значение времени для точки "куда"

        if (edgeTo_stScheme_nextChPointID_ordinal.find(edge_ID_ID) !=
            edgeTo_stScheme_nextChPointID_ordinal.end())//Если ВС на стандартной схеме
        {
            switch (edgeTo_stScheme_nextChPointID_ordinal[edge_ID_ID].second)
            { //ts - time segment
                case 1: //ВС на первом участке ст. схемы. Считаем для второй, третьей и первой точек временные интервалы

                    const pair<Time, Time> second_point_ts = //Время за дугу окружности
                            plane_arc_Time(zone.checkPoints[edge_ID_ID.first],
                                           zone.checkPoints[edge_ID_ID.second], plane);


                    const pair<Time, Time> &line =
                            checkPoint_checkPoint_Time(zone.checkPoints[edge_ID_ID.second],
                                                       zone.checkPoints[edgeTo_stScheme_nextChPointID_ordinal[edge_ID_ID].first]);


                    const pair<Time, Time> third_point_ts = //Время за дугу + прямая
                            second_point_ts + //Дуга
                            line;//Прямая


                    const pair<Time, Time> semicircle_T = semicircle_Time(zone.checkPoints[edge_ID_ID.second], //Время для полуокружности
                                                                          zone.checkPoints[edge_ID_ID.first]);


                    const pair<Time, Time> first_point_ts = //Мин: дуга + дуга, Макс: дуга + линия + дуга + линия
                            {second_point_ts.first //Мин времени по первой дуге
                             + semicircle_T.first //Мин времени по обратной дуге
                                    ,
                             third_point_ts.second //Макс до третьей точки
                             + semicircle_T.second //Макс по дуге
                             + line.second //Макс по прямой
                            };

                    //TODO перегрузить << для pair<Times, Times>
                    cout << zone.checkPoints[edge_ID_ID.second].name << " --> " << second_point_ts << endl;


                         //TODO доделать согласно картинке.

                         Time
                    A, B, C;


                    break;
            }

        }
        else
        {
            initialTimes(flow, zone.checkPoints, plane, edge_ID_ID, ID_there);//Записали временные интервалы

            //Ищем номер вершины "куда" в топологичеком порядке потока
            auto it_index_there = find(flow.keys.begin(), flow.keys.end(), ID_there);
            const int top_ID_there = it_index_there - flow.keys.begin();


            calculateTimes(flow, zone.checkPoints, zone.standardSchemes, top_ID_there);//Рассчитываем все времена, которые "ниже по течению"
            zone.flows[0].print_times();//Сливаем куда-то
            flow.times.clear();
            return 0;
        }
    }
