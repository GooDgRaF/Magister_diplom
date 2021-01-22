//
// Created by Антон on 14.01.2021.
//

#include <Fields of Zone/Maps.h>
#include <Functions/Geometric functions/Nearest point from the center to .h>
#include "Calculate times new plane.h"
#include "Functions/Times functions/Calculate times.h"
#include <Functions/Times functions/Initialization of time segments.h>
#include <Functions/Times functions/Arc time.h>
#include <Functions/Times functions/Time segment from point to checkPoint.h>


int topID(Flow &flow, const int point_ID);

void
calc_and_initStScheme(Flow &flow, const vector<CheckPoint> &checkPoints, const PlanePoint &plane, const pair<int, int> &edge_ID_ID);

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
            calc_and_initStScheme(flow, zone.checkPoints, plane, edge_ID_ID);

            calculateTimes(flow, zone.checkPoints, zone.standardSchemes, //Рассчитываем все времена, которые "ниже по течению"
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

void
calc_and_initStScheme(Flow &flow, const vector<CheckPoint> &checkPoints, const PlanePoint &plane, const pair<int, int> &edge_ID_ID)
    {
        StandardScheme stScheme = edgeTo_stScheme_part[edge_ID_ID].first;
        const int start_ID = stScheme.start_ID;
        const int second_ID = stScheme.second_ID;
        const int third_ID = stScheme.third_ID;

        //TODO ВНИМАТЕЛЬНО посмотреть, где нужна четвёртая точка из stScheme

        switch (edgeTo_stScheme_part[edge_ID_ID].second)//Номер части, где находится ВС на ст. схеме
        { //ts - time segment
            case 1: //ВС на первом участке ст. схемы. Считаем для второй, третьей и первой точек временные интервалы
            {
                const pair<Time, Time> second_point_ts = //Время за дугу окружности
                        plane_arc_Time(checkPoints[start_ID],
                                       checkPoints[second_ID], plane);

                const pair<Time, Time> third_point_ts = //Время за дугу + прямая
                        second_point_ts + //Дуга
                        stScheme.line_T;//Прямая

                const pair<Time, Time> start_point_ts = //Мин: дуга + дуга, Макс: дуга + линия + дуга + линия
                        {second_point_ts.first //Мин времени по первой дуге
                         + stScheme.semicircle_T.first //Мин времени по обратной полуокружности
                                ,
                         third_point_ts.second //Макс до третьей точки
                         + stScheme.semicircle_T.second //Макс по обратной полуокружности
                         + stScheme.line_T.second //Макс по прямой
                        };


                cout << checkPoints[second_ID].name << " --> " << second_point_ts << endl;
                cout << checkPoints[third_ID].name << " --> " << third_point_ts << endl;
                cout << checkPoints[start_ID].name << " --> " << start_point_ts << endl;

                flow.times[start_ID].push_back(start_point_ts);//Временной интервал точки конца ст. схемы проинициализировали
                break;
            }

            case 2://ВС на прямом обратном участке
            {
                const pair<Time, Time> third_point_ts = //Время по прямой
                        plane_checkPoint_Time(plane, stScheme.third);

                const pair<Time, Time> start_point_ts = //Мин: дуга + кусок прямой, Макс: линия + дуга + линия
                        {plane_checkPoint_Time(plane, stScheme.second).first//Мин времени до точки
                         + stScheme.semicircle_T.first //Мин времени по обратной полуокружности
                                ,
                         third_point_ts.second //Макс до третьей точки
                         + stScheme.semicircle_T.second //Макс по обратной полуокружности
                         + stScheme.line_T.second //Макс по прямой
                        };

                cout << checkPoints[third_ID].name << " --> " << third_point_ts << endl;
                cout << checkPoints[start_ID].name << " --> " << start_point_ts << endl;

                flow.times[start_ID].push_back(start_point_ts);//Временной интервал точки конца ст. схемы проинициализировали
                break;
            }
                //TODO доделать согласно картинке.

                /*case 3:
                {
                    const pair<Time, Time> arc_time = plane_arc_Time(stScheme.third, );
                    const pair<Time, Time> start_point_ts = //Дуга + прямая
                            { //Мин времени по обратной дуге
                                    ,
                                    //Макс по дуге
                                    + stScheme.line_T.second //Макс по прямой
                            };

                    cout << checkPoints[start_ID].name << " --> " << start_point_ts << endl;

                    flow.times[start_ID].push_back(start_point_ts);//Временной интервал точки конца ст. схемы проинициализировали

                    break;
                }*/
            default: cerr << "Foreign object in edgeTo_stScheme_part.second" << endl;
                exit(-1);
        }
    }

int topID(Flow &flow, const int point_ID)
    {
        auto it_index_there = find(flow.keys.begin(), flow.keys.end(), point_ID);
        const int top_ID_there = it_index_there - flow.keys.begin();
        return top_ID_there;
    }
