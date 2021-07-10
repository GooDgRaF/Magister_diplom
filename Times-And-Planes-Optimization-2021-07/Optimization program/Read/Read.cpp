//
// Created by Антон on 07.07.2021.
//

#include "Read.h"
#include "Optimization program/Zone.h"
#include "Assistant.h"
#include <regex>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


void read_checkPoints(string_view path)
    {
        zone.checkPoints.resize(count_number_of_line(path) - 1);
        
        ifstream file{};
        openFile(path, file);
        
        string x_mu{}, y_mu{}, z_mu{}, Vmin_mu{}, Vmax_mu{};
        file >> x_mu >> y_mu >> z_mu >> Vmin_mu >> Vmax_mu; //Собрали информацию о единицах измерений
        
        /*
         * Пояснение к регулярному выражению:
         * Всего 7 групп захвата, согласно формату:
         *
         * NameP x y z v1 v2 land_flag
         *
         * 1) - имя точки [NameP], начинается с буквы
         * 2,3,4) - координаты x,y,z
         * 5,6) - скорости vmin, vmax
         * 7) - флаг посадочной полосы - LAND или пусто или 0
         */
        
        string line{};
        cmatch res{};
        regex regular(R"(([a-z,A-Z]\w*)\s+([-+]?[0-9]*\.?[0-9]+)\s+([-+]?[0-9]*\.?[0-9]+)\s+([-+]?[0-9]*\.?[0-9]+)\s+([0-9]*\.?[0-9]+)\s+([0-9]*\.?[0-9]+)\s*(LAND|0)?\s*)");
        
        getline(file, line);// Пропустить первую строку с единицами измерений
        int count_land_flag{0};
        for (int i = 0; i < zone.checkPoints.size(); ++i)
        {
            getline(file, line);
            if (!regex_match(line.c_str(), res, regular))
            {
                cerr << "Warning! Line '" << i + 2 << "' in " << path << " doesn't follow the input format." << endl;
                exit(FILE_NOT_ALLOWED_FORMAT);
            }
            for (const auto &el : zone.checkPoints) //Проверка, чтобы две точки с одинаковым названием не встречались
            {
                if (el.name == res[1])
                {
                    cerr << "Attention! '" << res[1] << "' point occurs twice in " << path << endl;
                    exit(DUPLICATE_NAME);
                }
            }
            double x_value, y_value, z_value, v_min, v_max;
            x_value = stod(string(res[2]));
            y_value = stod(string(res[3]));
            z_value = stod(string(res[4]));
            v_min = stod(string(res[5]));
            v_max = stod(string(res[6]));
            
            auto &checkPoint = zone.checkPoints[i];
            checkPoint.name = res[1];
            checkPoint.ID = i;
            checkPoint.x = {x_value, x_mu};
            checkPoint.y = {y_value, y_mu};
            checkPoint.z = {z_value, z_mu};
            checkPoint.Vmin = {v_min, Vmin_mu};
            checkPoint.Vmax = {v_max, Vmax_mu};
            
            if (res[7] == "LAND")
            {
                checkPoint.landing_flag = true;
                count_land_flag++;
                
                zone.final_point = i;
            }
            zone.pointName_to_ID.insert({res[1], i});
        }
        file.close();
        
        if (count_land_flag != 1)
        {
            cerr << "Check amount of 'LAND' flag! In " << path << endl;
            exit(FILE_NOT_ALLOWED_FORMAT);
        }
    }

void fill_scheme_field(sub_match<const char *> str, vector<int> &field)
    {
        std::stringstream ss({string(str)});
        string token{};
        while (ss >> token)
        {
            try
            {
                field.push_back(zone.pointName_to_ID.at(token));
            }
            catch (const std::out_of_range &ex)
            {
                throw std::runtime_error(token);
            }
        }
    }


void read_schemes(string_view path)
    {
        zone.schemes.resize(count_number_of_line(path));
        
        ifstream file{};
        openFile(path, file);
        
        /*
         * Пояснение к регулярому выражению:
         * Всего 6 групп захвата, согласно формату:
         *
         * P0 P1 ... [type]StrFrom(F0 F1 ...) StrTo(T0 T1 ...) K0 K1 ...
         *
         * 1) Точки предшествующие спрямлению [P0 P1 ...]
         * 2) Тип спрямления [type]: F(an) - веер, T(rombone) - полутромбон, O(uter) - внешнее, I(nner) - внутреннее
         * 3) Точки откуда можно спрямляться [F0 F1 ...]
         * 4) Точки на которые можно спрямляться [T0 T1 ...]
         * 5) Точки после спрямления [K0 K1 ...]
         *
         * Если спрямления нет, то группы 2,3,4,5 - пустые
         */
        
        string line{};
        cmatch res{};
        regex regular(R"(([\w\s]*)(?:\[(F|T|O|I)\]StrFrom\(([\w\s]+)\)\s*StrTo\(([\w\s]+)\))?([\w\s]*))");
        
        for (int i = 0; i < zone.schemes.size(); ++i)
        {
            getline(file, line);
            if (!regex_match(line.c_str(), res, regular))
            {
                cerr << "Warning! Line '" << i + 1 << "' in " << path << " doesn't follow the input format." << endl;
                exit(FILE_NOT_ALLOWED_FORMAT);
            }
            
            auto &scheme = zone.schemes[i];
            scheme.ID = i;
            if (auto str_type = string(res[2]); !str_type.empty())
                scheme.type = str_type;
            try
            {
                fill_scheme_field(res[3], scheme.straighteningFrom);
                fill_scheme_field(res[4], scheme.straighteningTo);
    
                for (const auto pointTo : scheme.straighteningTo)
                {
                    for (const auto pointFrom : scheme.straighteningFrom)
                    {
                        zone.point_to_strFrom[pointTo].insert(pointFrom);
                    }
                }
                
                fill_scheme_field(res[1], scheme.path);
                fill_scheme_field(res[3], scheme.path);
                fill_scheme_field(res[5], scheme.path);
            }
            catch (const runtime_error &ex) //Ловим ошибку о не обнаружении точки из схемы среди точек из checkPoints
            {
                cerr << "Can't find '" << ex.what() << "' in line '" << i + 1
                     << "' among points from Points file" << endl;
                exit(NO_OBJECT);
            }
        }
        file.close();
    }

void read_holding_areas(std::string_view path)
    {
        zone.holdingAreas.resize(count_number_of_line(path));
        
        ifstream file{};
        openFile(path, file);
        
        
        /*
         *  SOMETHING
         */
        string line{};
        cmatch res{};
        regex regular(R"((\w+)\s*:\s*([0-9]*\.?[0-9]+)(s|min|h)\s*([0-9]*\.?[0-9]+)(s|min|h)\s*)");
        for (int i = 0; i < zone.holdingAreas.size(); ++i)
        {
            getline(file, line);
            if (!regex_match(line.c_str(), res, regular))
            {
                cerr << "Warning! Line '" << i + 1 << "' in " << path << " doesn't follow the input format." << endl;
                exit(FILE_NOT_ALLOWED_FORMAT);
            }
            
            auto &hA = zone.holdingAreas[i];
            hA.ID = i;
            
            //SOMETHING
            try
            {
                zone.point_to_holdingArea.insert({zone.pointName_to_ID.at(res[1]), hA.ID});
            }
            catch (const out_of_range &ex) //Ловим ошибку о не обнаружении точки среди точек из checkPoints
            {
                cerr << "Can't find '" << string(res[1]) << "' in line '" << i + 1
                     << "' among points from Points file" << endl;
                exit(NO_OBJECT);
            }
            
            auto t_minMU = string(res[3]);
            auto t_min = stod(string(res[2]));
            hA.t_min = {t_min, t_minMU};
            
            auto t_maxMU = string(res[5]);
            auto t_max = stod(string(res[4]));
            hA.t_max = {t_max, t_maxMU};
        }
        file.close();
    }


void openFile(const string_view &path, ifstream &openFile)
    {
        openFile.open(string(path));
        if (!openFile.is_open())
        {
            cerr << "Error! File " << path << " does not exist!" << endl;
            exit(FILE_NOT_EXIST);
        }
    }

int count_number_of_line(string_view path)
    {
        ifstream checkPointFile{};
        openFile(path, checkPointFile);
        int i{};
        string tmp{};
        while (getline(checkPointFile, tmp))
            i++;
        return i;
    }

