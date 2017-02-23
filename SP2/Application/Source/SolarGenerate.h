#ifndef _SOLAR_GENERATE_H
#define _SOLAR_GENERATE_H

#include "GalaxyGenerate.h"
#include "ObjectRender.h"
#include "ObjectFactory.h"

class SolarGenerate
{
public:
	SolarGenerate(SystemScene*);
	~SolarGenerate();

	void Init();
	void save_init();
	void update();
	void build_system(float,float);
	int num_of_planet_getter();

private:

	int number_of_planets;
	SystemScene* myscene;
	ObjectFactory objfactory;
};

#endif