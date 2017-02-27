#ifndef _SOLAR_GENERATE_H
#define _SOLAR_GENERATE_H

#include "ObjectRender.h"
#include "ObjectFactory.h"

#include <vector>
#include <map>
using std::vector;
using std::map;

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
	int planetID_getter();
	vector<ObjectRender*> planet_storage_getter();

	int planet_type;

private:

	int planetID;
	//int planet_type = 0;
	vector<ObjectRender*> planet_storage;
	int number_of_planets;
	SystemScene* myscene;
	ObjectFactory objfactory;
};

#endif