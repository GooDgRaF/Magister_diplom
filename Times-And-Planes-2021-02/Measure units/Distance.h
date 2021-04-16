//
// Created by Антон on 17.04.2020.
//

#ifndef TIMES_AND_PLANES_COORDINATE_H
#define TIMES_AND_PLANES_COORDINATE_H


#include "Time.h"

class Distance
{
	double coordinate_ms; //В метрах
	
	Distance(double d);

public:
	static constexpr double Km2ms = 1000;
	
	static constexpr double NMs2ms = 1852;
	
	double getMs() const;
	
	double getKms() const;
	
	double getNMs() const;
	
	static Distance createM(double m);
	
	static Distance createKm(double km);
	
	static Distance createNM(double nm);
	
	Distance operator+() const;
	
	Distance operator-() const;
};


#endif //TIMES_AND_PLANES_COORDINATE_H
