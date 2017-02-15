#ifndef _LAND_GENERATE_H
#define _LAND_GENERATE_H

#include "GalaxyGenerate.h"
#include "Vector3.h"
#include "Randomise.h"

class LandGenerate
{
public:
	LandGenerate();
	~LandGenerate();

	void landInIt();		//newInit
	void saveLandInIt();	//reloadInit
	void landUpdate();


protected:

	typedef vector<vector<int>> double_land_array;
	typedef vector<vector<double_land_array>> double_double_land_array;

	double_land_array land_inner_grid;
	double_double_land_array land_outer_grid;
	
	vector<double_land_array> test;

private:

	unsigned landID;
	Randomise* random;
};

#endif