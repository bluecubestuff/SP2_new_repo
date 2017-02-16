#ifndef _LAND_GENERATE_H
#define _LAND_GENERATE_H

#include "GalaxyGenerate.h"
#include "Building.h"
#include "ObjectFactory.h"
#include "Vector3.h"

class LandGenerate
{
public:

	typedef vector<vector<LandGenerate*>> double_land_array;
	//typedef vector<vector<double_land_array>> double_double_land_array;

	LandGenerate();
	~LandGenerate();

	void landInIt();				//newInit
	void saveLandInIt(unsigned);	//reloadInit
	void landUpdate();

	//void buildingLand(double_double_land_array);
	//double_double_land_array getter();

	//double_double_land_array land_outer_grid;
	//vector<double_land_array> tempStore;
	//vector<double_double_land_array> landDataBase;

private:

	double_land_array land_inner_grid;
	ObjectFactory* Obj_factory;
	ObjectRender* tester;
	Building* land_building;
	
	unsigned landID;
};

#endif