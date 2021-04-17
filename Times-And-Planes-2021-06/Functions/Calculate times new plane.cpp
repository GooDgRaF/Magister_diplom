//
// Created by Антон on 14.01.2021.
//

#include <Fields of Zone/Maps.h>
#include <Functions/Geometric functions/Nearest point from the center to .h>
#include "Calculate times new plane.h"
#include "Functions/Times functions/Calculate_times.h"
#include <Functions/Times functions/Initialization of time segments.h>
#include <Functions/Times functions/Calc time segments for StScheme.h>

using namespace std;

int topID(Flow &flow, const int point_ID);

map<int, vector<pair<double, double>>>
part_of_times(map<int, vector<pair<Time, Time>>> &times, const vector<int> &ID_for_return);

void checkError(const PlanePoint &plane);

/**
 Функция принимает на вход Зону, объект типа самолёт и вектор ID точек.
 Возвращает возможные временные промежутки прибытия ВС на эти точки.
*/
void
calc_plane(Zone &zone, const PlanePoint &plane,
           map<int, vector<pair<double, double>>> &result,
           map<int, vector<pair<pair<double, double>, int>>> &not_merged_result,
           const vector<int> &ID_points_to_calculate)
    {
        checkError(plane);

        Flow &flow = zone.flows[flowNameToID[plane.flow_for_plane]];
        const pair<int, int> edge_ID_ID = {pointNameToID[plane.on_edge.first],
                                           pointNameToID[plane.on_edge.second]};


        initialTimes(flow, zone.checkPoints, plane, edge_ID_ID); // Инициировали ближайшие точки и ст схему, если имеется
        int &there_ID = pointNameToID[plane.destination];//ID точки "куда"
        calc_TimeSegments(flow, zone.checkPoints, zone.standardSchemes, topID(flow, there_ID));//Рассчитываем все времена, которые "ниже по течению"
//        not_merged_result = part_of_times(flow.not_merged_times, ID_points_to_calculate);
        result = part_of_times(flow.times, ID_points_to_calculate);

    }

void checkError(const PlanePoint &plane)
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
