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

map<int, vector<pair<double, double>>>
part_of_times(map<int, vector<pair<Time, Time>>> &times, const vector<int> &ID_for_return);

/*
 Функция принимает на вход Зону, объект типа самолёт и вектор ID точек.
 Возвращает возможные временные промежутки прибытия ВС на эти точки.
*/


map<int, vector<pair<double, double>>>
calc_plane(Zone &zone, const PlanePoint &plane, const vector<int> &ID_points_to_calculate)
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
            exit(-1);
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

            return part_of_times(flow.times, ID_points_to_calculate);
        }
        else
        {
            const int ID_there = pointNameToID[plane.destination];//Записываем ID точки "куда"
            initialTimes(flow, zone.checkPoints, plane, edge_ID_ID, ID_there);//Записали временные интервалы          
            calculateTimes(flow, zone.checkPoints, zone.standardSchemes, topID(flow, ID_there));//Рассчитываем все времена, которые "ниже по течению"

            return part_of_times(flow.times, ID_points_to_calculate);
        }
    }

map<int, vector<pair<double, double>>>
part_of_times(map<int, vector<pair<Time, Time>>> &times, const vector<int> &ID_for_return)
    {
        map<int, vector<pair<double, double>>> ID_to_TS_sec;//Возвращаем отображение ID точки --> набор временных сегментов в секундах
        for (const auto &elem : times)
        {
            int ID = elem.first;
            if ((ID_for_return.empty())
                || (find(ID_for_return.begin(), ID_for_return.end(), ID) != ID_for_return.end()))
            {
                vector<pair<double, double>> v_ts;//Вектор временных сегментов
                for (const auto &ts : elem.second)
                {
                    v_ts.emplace_back(ts.first.getTsec(), ts.second.getTsec());
                }

                ID_to_TS_sec[ID] = v_ts;

                v_ts.clear();
            }
        }

        times.clear();
        return ID_to_TS_sec;
    }


int topID(Flow &flow, const int point_ID)
    {
        auto it_index_there = find(flow.keys.begin(), flow.keys.end(), point_ID);
        const int top_ID_there = it_index_there - flow.keys.begin();
        return top_ID_there;
    }
