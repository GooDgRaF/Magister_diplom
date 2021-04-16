//
// Created by Антон on 18.01.2021.
//

#include <sstream>
#include "Hesh mu_vector.h"

void sum_char_mu(const std::string &str, std::vector<int> &v)
    {
        std::stringstream ss(str);
        std::string token;
        while (ss >> token)
        {
            int sum = 0;
            for (auto c : token)
            {
                sum += c;
            }
            v.push_back(sum);
        }
    }
