#ifndef _SOLAR_GENERATE_H
#define _SOLAR_GENERATE_H

#include "ObjectRender.h"
#include "ObjectFactory.h"
#include "LandGenerate.h"

#include <vector>
#include <map>
using std::vector;
using std::map;

typedef map<int, LandGenerate*> LandDataBase;

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
	//int planetID_getter();
	int solar_system_ID_getter();
	vector<ObjectRender*> planet_storage_getter();

	int planet_type;
	LandDataBase land_database;	//store the land_data;

private:

	int SolarSystemID;
	//int planetID;
	//int planet_type = 0;

	vector<ObjectRender*> planet_storage;			//store the objects in solar system 
	
	int number_of_planets;
	SystemScene* myscene;
	ObjectFactory* objfactory;
};

#endif