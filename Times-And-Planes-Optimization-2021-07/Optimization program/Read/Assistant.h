//
// Created by Антон on 07.07.2021.
//

#ifndef TIMES_AND_PLANES_OPTIMIZATION_2021_07_ASSISTANT_H
#define TIMES_AND_PLANES_OPTIMIZATION_2021_07_ASSISTANT_H
#include "string_view"
#include "iostream"
#include <fstream>
#include "Optimization program/Errors/Errors.h"

void openFile(const std::string_view &path, std::ifstream &openFile)
    {
        openFile.open(std::string(path));
        if (!openFile.is_open())
        {
            std::cerr << "Error! File "<< path << " does not exist!" << std::endl;
            exit(FILE_NOT_EXIST);
        }
    }

int count_number_of_line(std::string_view path)
    {
        std::ifstream checkPointFile;
        openFile(path, checkPointFile);
        
        int i{};
        std::string tmp;
        while (getline(checkPointFile, tmp))
            i++;
        return i;
    }
#endif //TIMES_AND_PLANES_OPTIMIZATION_2021_07_ASSISTANT_H
