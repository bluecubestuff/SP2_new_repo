#ifndef _LAND_GENERATE_H
#define _LAND_GENERATE_H

#include "Vector3.h"
#include "ObjectRender.h"
#include "ObjectFactory.h"

#include <vector>
#include <map>
using std::vector;
using std::map;

typedef vector<vector<unsigned>> double_land_array;

class LandGenerate
{
public:
	LandGenerate(StudioProject*);
	LandGenerate(PlanetScene*);
	~LandGenerate();

	void landInIt();				//newInit
	void saveLandInIt();	//reloadInit
	void landUpdate();
	void BuildLand();
	void SetPath();

	ObjectFactory object_factory_getter();
	int planet_id_getter();

	char path[2500][2500];
	map<unsigned, vector<ObjectRender*>> obj_data_at_box;
	int noOfEnemies;
	vector<Vector3> enemy_positions;
	vector<int> enemy_type;

private:

	vector<ObjectRender*> obj_storage;
	Vector3 obj_pos;

	StudioProject* myscene;
	PlanetScene* planet_scene;
	ObjectFactory objectfactory;

	int sceneID;		//the scene's ID
	int SystemID;		//the solar system's ID
	int PlanetID;		//the planet's ID
};

#endif