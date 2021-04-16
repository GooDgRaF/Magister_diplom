//
// Created by Антон on 24.03.2020.
//

#ifndef TIMES_AND_PLANES_FIND_INVECTOR_H
#define TIMES_AND_PLANES_FIND_INVECTOR_H

#include <algorithm>

template<typename T>
bool findInVectorBool(const std::vector<T> &v, T value)
	{
		return find(v.begin(), v.end(), value) != v.end();
	}

#endif //TIMES_AND_PLANES_FIND_INVECTOR_H
