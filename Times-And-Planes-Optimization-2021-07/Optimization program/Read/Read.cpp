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
        ifstream checkPointFile;
        openFile(path, checkPointFile);
        int i{};
        string tmp;
        while (getline(checkPointFile, tmp))
            i++;
        return i;
    }

void fill_scheme_field(sub_match<const char *> str, vector<int> &field)
    {
        std::stringstream ss({string(str)});
        string token;
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

void read_CheckPoints(string_view path)
    {
        zone.checkPoints.resize(count_number_of_line(path) - 1);
        
        ifstream file;
        openFile(path, file);
        
        string x_mu, y_mu, z_mu, Vmin_mu, Vmax_mu;
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
        
        string line;
        cmatch res;
        regex regular(R"(([a-z,A-Z]\w*)\s+([-+]?[0-9]*\.?[0-9]+)\s+([-+]?[0-9]*\.?[0-9]+)\s+([-+]?[0-9]*\.?[0-9]+)\s+([0-9]*\.?[0-9]+)\s+([0-9]*\.?[0-9]+)\s*(LAND|0)?\s*)");
        
        getline(file, line);// Пропустить первую строку с единицами измерений
        int count_land_flag{0};
        for (int i = 0; i < zone.checkPoints.size(); ++i)
        {
            getline(file, line);
            if (!regex_match(line.c_str(), res, regular))
            {
                cerr << "Warning! Line '" << i + 1 << "' in " << path << " doesn't follow the input format." << endl;
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
            
            zone.checkPoints[i].name = res[1];
            zone.checkPoints[i].ID = i;
            zone.checkPoints[i].x = {x_value, x_mu};
            zone.checkPoints[i].y = {y_value, y_mu};
            zone.checkPoints[i].z = {z_value, z_mu};
            zone.checkPoints[i].Vmin = {v_min, Vmin_mu};
            zone.checkPoints[i].Vmax = {v_max, Vmax_mu};
            
            if (res[7] == "LAND")
            {
                zone.checkPoints[i].landing_flag = true;
                count_land_flag++;
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

void read_Schemes(string_view path)
    {
        zone.schemes.resize(count_number_of_line(path));
        
        ifstream file;
        openFile(path, file);
        
        /*
         * Пояснение к регулярому выражению:
         * Всего 6 групп захвата, согласно формату:
         *
         * NameP: P0 P1 ... [type_of_str]Str(F0 F1 ...) T0 T1 ... /Str L0 L1 ...
         *
         * 1) Название точки начала схемы [NameP]
         * 2) Точки предшествующие спрямлению [P0 P1 ...]
         * 3) Тип спрямления [type_of_str]: F(an) - веер, T(rombone) - полутромбон, O(uter) - внешнее, B(elong) - конечная(ые) точки спрямления принадлежат схеме
         * 4) Точки на которые можно спрямляться [F0 F1 ...]
         * 5) Точки откуда можно спрямляться [T0 T1 ...]
         * 6) Точки после спрямления [L0 L1 ...]
         *
         * Если спрямления нет, то группы 3,4,5,6 - пустые
         */
        
        string line;
        cmatch res;
        regex regular(R"((\w+)\s*:([\w\s]*)(?:\[(F|T|O|B)\]Str\(([\w\s]+)\)([\w\s]+)\/Str)?([\w\s]*))");
        
        for (int i = 0; i < zone.schemes.size(); ++i)
        {
            getline(file, line);
            if (!regex_match(line.c_str(), res, regular))
            {
                cerr << "Warning! Line '" << i + 1 << "' in " << path << " doesn't follow the input format." << endl;
                exit(FILE_NOT_ALLOWED_FORMAT);
            }
            zone.schemes[i].ID = i;
            if (auto str_type = string(res[3]); !str_type.empty())
                zone.schemes[i].type = str_type;
            try
            {
                try
                { zone.schemes[i].start = zone.pointName_to_ID.at(string(res[1])); }
                catch (const out_of_range &ex)
                {
                    throw runtime_error(string(res[1]));
                }
                fill_scheme_field(res[4], zone.schemes[i].straighteningTo);
                fill_scheme_field(res[5], zone.schemes[i].straighteningFrom);
                
                fill_scheme_field(res[2], zone.schemes[i].path);
                fill_scheme_field(res[5], zone.schemes[i].path);
                fill_scheme_field(res[6], zone.schemes[i].path);
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

 
