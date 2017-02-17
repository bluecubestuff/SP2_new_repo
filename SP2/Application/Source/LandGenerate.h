#ifndef _LAND_GENERATE_H
#define _LAND_GENERATE_H

#include "GalaxyGenerate.h"
#include "ObjectFactory.h"
#include "Vector3.h"

typedef vector<vector<unsigned>> double_land_array;

class LandGenerate
{
public:
	//typedef vector<vector<double_land_array>> double_double_land_array;

	LandGenerate();
	~LandGenerate();

	void landInIt();				//newInit
	void saveLandInIt(unsigned);	//reloadInit
	void landUpdate();
	double_land_array getter();

	int outer_grid[10][10];
	
	//void buildingLand(double_land_array);
	//double_double_land_array land_outer_grid;
	//vector<double_land_array> tempStore;
	//vector<double_double_land_array> landDataBase;

private:

	double_land_array land_inner_grid;
	
	unsigned landID;
};

#endif