//
// Created by Антон on 22.04.2020.
//

#include "Read_CheckPointsRegExp.h"
#include <regex>
#include <fstream>
#include <Functions/Assistant functions/OpenFile.h>
#include <Functions/Assistant functions/Hesh mu_vector.h>
#include <Fields of Zone/Maps.h>
#include "Functions/Assistant functions/Fill checkPoint coordinate and velocity.h"

using namespace std;

void Read_CheckPointsRegExp(const std::string &name_of_file, std::vector<CheckPoint> &checkPoints)
    {
        ifstream CheckPointFile;
        openFile(name_of_file, CheckPointFile);
        {
            int i;
            CheckPointFile >> i; //Первым лежит значение сколько точек всего

            string tmp;//Прочитать остаток строки
            getline(CheckPointFile, tmp);

            if (i <= 0)
            {
                cerr << "Warning put the correct value for the number of points in " << name_of_file << endl;
                exit(-2);
            }

            checkPoints.resize(i);
        }


        vector<int> measure_units; //Заполняем вектор единиц измерений
        {
            string str_mu;
            getline(CheckPointFile, str_mu);
            sum_char_mu(str_mu, measure_units);
        }




        /*
         * Пояснение к регулярному выражению:
         * Всего 7 групп захвата, согласно формату:
         * NameP x y z v1 v2 land_flag
         * 1) - имя точки [NameP], начинается с буквы
         * 2,3,4) - координаты x,y,z
         * 5,6) - скорости vmin, vmax
         * 7) - флаг посадочной полосы - LAND или пусто либо 0
         */

        string str;
        cmatch res;
        regex regular(R"(([a-z,A-Z]\w*)\s+([-+]?[0-9]*\.?[0-9]+)\s+([-+]?[0-9]*\.?[0-9]+)\s+([-+]?[0-9]*\.?[0-9]+)\s+([0-9]*\.?[0-9]+)\s+([0-9]*\.?[0-9]+)\s*(LAND|0)?\s*)");

        int i = 0; //Счётчик, отвечающий за проход по checkpoints
        int k = 0; //Счётчик, отвечающщий за точку с флагом LAND



        while (getline(CheckPointFile, str))
        {
            if (!regex_match(str.c_str(), res, regular))
            {
                cerr << "Warning! Line '" << i + 2 << "' in " << name_of_file << " doesn't follow the input format"
                     << endl;
                exit(-3);
            }

            for (const auto &el : checkPoints) //Проверка, чтобы две точки с одинаковым названием не встречались
            {
                if (el.name == res[1])
                {
                    cerr << "Attention! '" << res[1] << "' point occurs twice in " << name_of_file << endl;
                    exit(-2);
                }
            }

            enum Position
            {
                x_position = 0, y_position, z_position, v_min_position, v_max_position
            };


            double x_value, y_value, z_value, v_min, v_max;
            try
            {
                checkPoints.at(i); //Проверка доступа к i-ой координате вектора checkPoints

                x_value = stod(string(res[2]));
                y_value = stod(string(res[3]));
                z_value = stod(string(res[4]));
                v_min = stod(string(res[5]));
                v_max = stod(string(res[6]));
            }
            catch (const out_of_range &ex) //Ловим ошибку о нехватке выделенного места для входных данных
            {
                cerr << "Check in " << name_of_file << " amount of points, it is low" << endl;
                exit(-2);
            }
            catch (const invalid_argument &ex) //Не бывает
            {
                cerr << "Warning! Line '" << i + 2 << "' in " << name_of_file << " doesn't follow the input format"
                     << endl;
                exit(-3);
            }

            checkPoints[i].name = res[1];

            // Заполняем в зависимости от исходных данных
            fill_checkPoint_coordinate(checkPoints[i].x, measure_units[x_position], x_value);
            fill_checkPoint_coordinate(checkPoints[i].y, measure_units[y_position], y_value);
            fill_checkPoint_coordinate(checkPoints[i].z, measure_units[z_position], z_value);

            fill_checkPoint_velocity(checkPoints[i].Vmin, measure_units[v_min_position], v_min);
            fill_checkPoint_velocity(checkPoints[i].Vmax, measure_units[v_max_position], v_max);


            if (res[7] == "LAND")
            {
                checkPoints[i].landing_flag = true;
                k++;
                if (k > 1)
                {
                    cerr << "Attention! in " << name_of_file << " was found more than one points with 'LAND' flag"
                         << endl;
                    exit(-3);
                }
            }


            pointNameToID[checkPoints[i].name] = i;


            if (v_min > v_max) //Проверка корректности введённых скоростей
            {
                cerr << "Attention! v_min = " << v_min << " > v_max = " << v_max << " in file: " << name_of_file
                     << " in line: " << i + 2 << endl;
                exit(-3);
            }

            i++;
        }
        if (k == 0)
        {
            {
                cerr << "Attention! in " << name_of_file << " wasn't found no one points with 'LAND' flag" << endl;
                exit(-3);
            }
        }

        if (checkPoints.size() >
            i) //На случай если число точек считанное из файла, больше действительного их количества
        {
            checkPoints.resize(i);
        }

        CheckPointFile.close();

    }