#ifndef _LAND_GENERATE_H
#define _LAND_GENERATE_H

#include "GalaxyGenerate.h"
#include "Vector3.h"

typedef vector<vector<unsigned>> double_land_array;

class LandGenerate
{
public:

	LandGenerate();
	~LandGenerate();

	void landInIt();				//newInit
	void saveLandInIt(unsigned);	//reloadInit
	void landUpdate();             
	double_land_array getter();

	double_land_array land_inner_grid;
	int outer_grid[10][10];

private:
	unsigned landID;

};

#endif