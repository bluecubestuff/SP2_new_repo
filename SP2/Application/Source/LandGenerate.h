#ifndef _LAND_GENERATE_H
#define _LAND_GENERATE_H

#include "GalaxyGenerate.h"
#include "Vector3.h"
#include "Randomise.h"
#include "ObjectRender.h"
#include "ObjectFactory.h"
#include <map>

typedef vector<vector<unsigned>> double_land_array;

class LandGenerate
{
public:
	LandGenerate(StudioProject*);
	LandGenerate(PlanetScene*);
	~LandGenerate();

	void landInIt();				//newInit
	void saveLandInIt(unsigned);	//reloadInit
	void landUpdate();
	void BuildLand();
	void SetPath();

	//double_land_array double_land_getter();
	ObjectFactory object_factory_getter();
	
	char path[2500][2500];
	map<unsigned, vector<ObjectRender*>> obj_data_at_box;

private:
	double_land_array land_inner_grid;
	vector<ObjectRender*> obj_storage;
	Vector3 obj_pos;

	StudioProject* myscene;
	PlanetScene* planet_scene;
	ObjectFactory objectfactory;
	int sceneID;
};

#endif