//
// Created by Антон on 17.04.2020.
//

#include "Distance.h"
#include "Velocity.h"
#include <cmath>

double Distance::getMs() const
	{
		return coordinate_ms;
	}

double Distance::getKms() const
	{
		return coordinate_ms / Km2ms;
	}

double Distance::getNMs() const
	{
		return coordinate_ms / NMs2ms;
	}

Distance Distance::createMs(double m)
	{
		return {m};
	}

Distance::Distance(double d)
	{
		coordinate_ms = d;
	}

Distance Distance::createKms(double km)
	{
		return {km * Km2ms};
	}

Distance Distance::createNMs(double nm)
	{
		return {nm * NMs2ms};
	}

Distance Distance::operator+() const
	{
		return {coordinate_ms};
	}

Distance Distance::operator-() const
	{
		return {-coordinate_ms};
	}

Distance operator+(const Distance &a, const Distance &b)
	{
		return Distance::createMs(a.getMs() + b.getMs());
	}

Distance operator-(const Distance &a, const Distance &b)
	{
		return Distance::createMs(a.getMs() - b.getMs());
	}

Distance operator*(const Time &t, const Velocity &v)
	{
		return Distance::createMs(t.getTsec() * v.getVm_s());
	}

Distance operator*(const Velocity &v, const Time &t)
	{
		return {t*v};
	}

Distance pow(Distance x, int a)
	{
		return Distance::createMs(std::pow(x.getMs(), a));
	}

Distance sqrt(Distance x)
	{
		return Distance::createMs(std::sqrt(x.getMs()));
	}

Distance operator*(const Distance &x, const double &a)
	{
		return Distance::createMs(x.getMs() * a);
	}

Distance operator*(const double &a, const Distance &x)
	{
		return Distance::createMs(a * x.getMs());
	}

Distance operator*(const Distance &x, const Distance &y)
    {
        return Distance::createMs(x.getMs() * y.getMs());
    }

Distance operator/(const Distance &x, const Distance &y)
    {
        return Distance::createMs(x.getMs() / y.getMs());
    }