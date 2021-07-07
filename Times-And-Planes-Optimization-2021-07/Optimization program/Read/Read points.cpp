//
// Created by Антон on 07.07.2021.
//

#include "Read points.h"
#include "Optimization program/Zone.h"
#include "Assistant.h"
#include <regex>
#include <fstream>
#include <string>
#include <Optimization program/Fields of Zone/Fields of Zone.h>

using namespace std;


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
         * NameP x y z v1 v2 land_flag
         * 1) - имя точки [NameP], начинается с буквы
         * 2,3,4) - координаты x,y,z
         * 5,6) - скорости vmin, vmax
         * 7) - флаг посадочной полосы - LAND или пусто или 0
         */
        
        string line;
        cmatch res;
        regex regular(R"(([a-z,A-Z]\w*)\s+([-+]?[0-9]*\.?[0-9]+)\s+([-+]?[0-9]*\.?[0-9]+)\s+([-+]?[0-9]*\.?[0-9]+)\s+([0-9]*\.?[0-9]+)\s+([0-9]*\.?[0-9]+)\s*(LAND|0)?\s*)");
        
        getline(file, line);// Пропустить первую строку с единицами измерений
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
            zone.checkPoints[i].x = {x_value,x_mu};
            zone.checkPoints[i].y = {y_value,y_mu};
            zone.checkPoints[i].z = {z_value,z_mu};
            zone.checkPoints[i].Vmin = {v_min, Vmin_mu};
            zone.checkPoints[i].Vmax = {v_max, Vmax_mu};
            
            if (res[7] == "LAND")
                zone.checkPoints[i].landing_flag = true;
    
            zone.pointName_to_ID.insert({res[1], i});
        }
        file.close();
    }
    
    
