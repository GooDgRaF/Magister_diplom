//
// Created by Антон on 23.01.2021.
//

#include <Fields of Zone/StandardScheme.h>
#include <Fields of Zone/Maps.h>
#include "Calc time segments for StScheme.h"
#include "Arc time.h"
#include "Time segment from point to checkPoint.h"

using namespace std;

void
calc_and_initStScheme(Flow &flow, const std::vector<CheckPoint> &checkPoints, const PlanePoint &plane, const std::pair<int, int> &edge_ID_ID, int &there_ID)
    {
        StandardScheme stScheme = edgeTo_stScheme_part[edge_ID_ID].first;
        const int start_ID = stScheme.start_ID;
        const int second_ID = stScheme.second_ID;
        const int third_ID = stScheme.third_ID;
        const int end_ID = stScheme.end_ID;

        there_ID = start_ID;

        //TODO ВНИМАТЕЛЬНО посмотреть, где нужна четвёртая точка из stScheme

        switch (edgeTo_stScheme_part[edge_ID_ID].second)//Номер части, где находится ВС на ст. схеме
        { //ts - time segment
            case 1: //ВС на первом участке ст. схемы. Считаем для второй, третьей, конечной и первой точек временные интервалы
            {
                const pair<Time, Time> second_point_ts = //Время за первую дугу окружности
                        plane_arc_Time(checkPoints[start_ID],
                                       checkPoints[second_ID], plane);

                const pair<Time, Time> third_point_ts = //Время первую за дугу + обратная прямая
                        second_point_ts + //Дуга
                        stScheme.line_back_T;//Прямая

                const pair<Time, Time> end_point_ts = //Время первую за дугу + обратная прямая + вторая окружность
                        third_point_ts +
                        stScheme.second_semicircle_T;

                const pair<Time, Time> start_point_ts = //Мин: почти круг, Макс: дуга + линия + полуокружность + линия
                        {second_point_ts.first //Мин времени по первой дуге
                         + stScheme.first_semicircle_T.first //Мин времени по полуокружности
                                ,
                         end_point_ts.second
                         + stScheme.line_forward_T.second //Макс по прямой
                        };


                cout << checkPoints[second_ID].name << ": " << second_point_ts << endl;
                cout << checkPoints[third_ID].name << ": " << third_point_ts << endl;
                cout << checkPoints[end_ID].name << ": " << end_point_ts << endl;

                flow.times[start_ID].push_back(start_point_ts);//Временной интервал точки конца ст. схемы проинициализировали
                break;
            }

            case 2://ВС на прямом обратном участке
            {
                const pair<Time, Time> third_point_ts = //Время по обратной прямой
                        plane_checkPoint_Time(plane, stScheme.third);

                const pair<Time, Time> end_point_ts =
                        third_point_ts + stScheme.second_semicircle_T;

                const pair<Time, Time> start_point_ts = //Мин: дуга + кусок прямой, Макс: обратная прямая + вторая дуга + линия
                        {plane_checkPoint_Time(plane, stScheme.second).first//Мин времени до точки начала (в другую сторону)
                         + stScheme.first_semicircle_T.first //Мин времени по обратной полуокружности
                                //TODO Узнать правильное время на промежуточной полуокружноти.
                                ,
                         end_point_ts.second
                         + stScheme.line_forward_T.second //Макс по прямой
                        };

                cout << checkPoints[third_ID].name << ": " << third_point_ts << endl;
                cout << checkPoints[end_ID].name << ": " << end_point_ts << endl;

                flow.times[start_ID].push_back(start_point_ts);//Временной интервал точки конца ст. схемы проинициализировали
                break;
            }

            case 3:
            {
                const pair<Time, Time> end_point_ts = plane_arc_Time(stScheme.third, stScheme.end, plane);
                const pair<Time, Time> start_point_ts = //Обратная дуга + прямая
                        {end_point_ts.first + //Мин времени по обратной дуге
                         stScheme.line_back_T.first //Мин времени по прямой
                                ,
                         end_point_ts.second + //Макс по дуге
                         stScheme.line_back_T.second //Макс по прямой
                        };

                cout << checkPoints[end_ID].name << ": " << end_point_ts << endl;

                flow.times[start_ID].push_back(start_point_ts);//Временной интервал точки конца ст. схемы проинициализировали
                break;
            }
            default: cerr << "Foreign object in 'edgeTo_stScheme_part.second'" << endl;
                exit(-1);
        }
    }
