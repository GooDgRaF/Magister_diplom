//
// Created by Антон on 10.02.2020.
//

#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <Functions/Assistant functions/Find-InVector-bool.h>
#include <Fields of Zone/Waiting area.h>
#include "Fields of Zone/Maps.h"
#include "Fields of Zone/Scheme.h"
#include "Functions/Assistant functions/OpenFile.h"
#include "Functions/Assistant functions/Fill-scheme.h"

using namespace std;

void
Read_SchemesRegExp(const string &name_of_file, vector<CheckPoint> &checkPoints, vector<Scheme> &schemes, vector<WaitingArea> &waitingAreas)
    {
        
        ifstream SchemeFile;
        openFile(name_of_file, SchemeFile);
        
        int i{-1}, k{-1};
        SchemeFile >> i; //Первым идёт количество схем
        SchemeFile >> k; //Потом количество стандартных схем
        
        if ((i <= 0) || (k < 0))
        {
            cerr << "Warning put the correct value for the number of schemes or standard schemes in " << name_of_file
                 << endl;
            exit(-2);
        }
        
        
        schemes.resize(i);
        waitingAreas.resize(k);
        
        /*
         * Пояснение к регулярным выражениям:
         *
         * reg_wa - регулярное для зоны ожидания
         * Шесть групп захвата:
         * NameWA (START_POINT): doubleMU doubleMU         *
         * 1) Название ЗО [NameWA]
         * 2) Название точки входа на ЗО [START_POINT]
         * 3) Положительное число [double] - минимальное время задержки в ЗО
         * 4) Единицы измерения [MU] --- 's' - секунды , 'min' - минуты , 'h' - часы
         * 5) Положительное число [double] - максимальное время задержки в ЗО
         * 6) Единицы измерения [MU] --- 's' - секунды , 'min' - минуты , 'h' - часы
         *
         *
         * reg_scheme - регулярное для схем
         * Всего семь групп захвата:
         * NameA (POINT1)(POINT12 POINT13): POINT1 POINT2 Str(POINT12 POINT13) POINT3 POINT4 POINT5 /Str POINT12
         * 1) Название схемы [NameA]
         * 2) Название точки начала схемы [POINT1]
         * 3) Названия точек конца схемы [POINT12 POINT13]
         * 4) Названия точек, предшествующих спрямлению [POINT1 POINT2]
         * 5) Названия точек куда можно спрямляться [POINT12 POINT13]
         * 6) Названия точек откуда можно спрямляться [POINT3 POINT4 POINT5]
         * 7) Названия точек следующих за спрямлением [POINT12]
         * 4,6,7) Названия образующие path [POINT1 POINT2 + POINT3 POINT4 POINT5 + POINT12]
         */
        
        string str;
        cmatch res;
        regex reg_wa(R"((\w+)\s*\((\w+)\)\s*:\s*([0-9]*\.?[0-9]+)(s|min|h)\s*([0-9]*\.?[0-9]+)(s|min|h)\s*)"),
                reg_scheme(
                R"((\w+)\s*\((\w+)\)\s*\(([\w\s]+)\)\s*:(?:\s*([\w\s]*)\s+(?:Str\(([\w\s]+)\)\s*([\w\s]+)\/Str)?\s*([\w\s]*)?)?)");
        i = 0; // Счётчик, отвечающий за проход по schemes
        k = 0; // Счётчик, отвечающий за проход по waitingArea
        
        getline(SchemeFile, str); //прочитать пустую строчку чтобы не мешалась
        
        while (getline(SchemeFile, str))
        {
            if (!regex_match(str.c_str(), res, reg_wa)) //Если не стандартная схема
            {
                if (!regex_match(str.c_str(), res, reg_scheme))
                {
                    cerr << "Warning! Line '" << i + k + 3 << "' in " << name_of_file
                         << " doesn't follow the input format"
                         << endl;
                    exit(-3);
                }
                try //Заполняем соответственно комментарию о регулярном выражении
                {
                    for (const auto &scheme : schemes) //Проверка, чтобы две схемы с одинаковым названием не встречались
                    {
                        if (scheme.name == res[1])
                        {
                            cerr << "Attention! '" << res[1] << "' scheme occurs twice in " << name_of_file << endl;
                            exit(-2);
                        }
                    }
                    
                    schemes.at(i); //Проверка доступа к i-ой координате вектора schemes
                    
                    if (string(res[4]).empty() && string(res[5]).empty()) //Схема из двух точек
                    {
                        schemes[i].name = string(res[1]);
                        
                        schemes[i].start = pointNameToID.at(string(res[2]));
                        
                        schemes[i].end.push_back(pointNameToID.at(string(res[3])));
                        
                        schemes[i].path.push_back(schemes[i].start);
                        schemes[i].path.push_back(schemes[i].end[0]);
                    }
                    else //Все остальные схемы
                    {
                        schemes[i].name = string(res[1]);
                        
                        schemes[i].start = pointNameToID.at(string(res[2]));
                        
                        fillScheme(string(res[3]), schemes[i].end);
                        
                        fillScheme(string(res[5]), schemes[i].straighteningWhere);
                        
                        fillScheme(string(res[6]), schemes[i].straighteningFrom);
                        
                        fillScheme(string(res[4]), schemes[i].path); //Собрали точки до спрямления
                        
                        for (auto el : schemes[i].straighteningFrom) //Собрали точки с которых возможно спрямление
                        {
                            schemes[i].path.push_back(el);
                        }
                        
                        fillScheme(string(res[7]), schemes[i].path); //Собрали точки после спрямления
                        
                        //Заполним отображение: ребро-->спрямление на точки
                        if (!schemes[i].straighteningFrom.empty())
                        {
                            for (int h = 0; h < schemes[i].straighteningFrom.size() - 1; h++)
                            {
                                edgeTo_ends_str_ID[
                                        {schemes[i].straighteningFrom[h],
                                         schemes[i].straighteningFrom[h + 1]}] = schemes[i].straighteningWhere;
                            }
                        }
                    }
                }
                catch (const runtime_error &ex) //Ловим ошибку о не обнаружении точки из схемы среди точек из checkPoints
                {
                    cerr << "Can't find '" << ex.what() << "' in line_back '" << i + k + 3
                         << "' among points from Points file"
                         << endl;
                    exit(-2);
                }
                catch (const out_of_range &ex) //Ловим ошибку о нехватке выделенного места для входных данных
                {
                    cerr << "Check in " << name_of_file << " amount of schemes, it is low" << endl;
                    exit(-2);
                }
                i++;
            }
            else
            {
                try //Заполняем соответственно комментарию о регулярном выражении
                {
                    waitingAreas.at(k); //Проверка доступа к k-ой координате вектора waitingArea
                    
                    waitingAreas[k].name = string(res[1]);
                    waitingAreas[k].entrance = pointNameToID.at(string(res[2]));
                    waitingAreas[k].ID = k;
                    waitingAreas[k].ts_min_max = {Time::create(stod(string(res[3])), string(res[4])),
                                                  Time::create(stod(string(res[5])), string(res[6]))};
                }
                catch (const runtime_error &ex) //Ловим ошибку о не обнаружении точки из стандартной схемы среди точек из checkPoints
                {
                    cerr << "Can't find '" << ex.what() << "' in line_back '" << i + k + 3
                         << "' among points from Points file"
                         << endl;
                    exit(-2);
                }
                catch (const out_of_range &ex) //Ловим ошибку о нехватке выделенного места для входных данных
                {
                    cerr << "Check in " << name_of_file << " amount of waiting areas, it is low" << endl;
                    exit(-2);
                }
                
                checkPointID_to_waID[waitingAreas[k].entrance] = k;
                k++;
            }
        }
        schemes.erase(remove_if(schemes.begin(), schemes.end(),
                                [](const Scheme &scheme){return scheme.path.empty();}), schemes.end());
        waitingAreas.erase(remove_if(waitingAreas.begin(), waitingAreas.end(),
                                [](const WaitingArea &waitingArea){return waitingArea.name.empty();}), waitingAreas.end());
        
        SchemeFile.close();
        
    }
