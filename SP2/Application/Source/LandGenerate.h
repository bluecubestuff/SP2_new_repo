#ifndef _LAND_GENERATE_H
#define _LAND_GENERATE_H

#include "GalaxyGenerate.h"
#include "Vector3.h"
#include "Randomise.h"

typedef vector<vector<unsigned>> double_land_array;
typedef vector<vector<double_land_array>> double_double_land_array;

class LandGenerate
{
public:

	LandGenerate();
	~LandGenerate();

	void landInIt();				//newInit
	void saveLandInIt(unsigned);	//reloadInit
	void landUpdate();
	void buildingLand(double_land_array);
	double_land_array getter();

private:
          
	double_land_array land_inner_grid;
	int outer_grid[10][10];

private:
	unsigned landID;

};

#endif