#ifndef _LAND_GENERATE_H
#define _LAND_GENERATE_H

#include "GalaxyGenerate.h"
#include "Vector3.h"

class LandGenerate
{
public:
	LandGenerate();
	~LandGenerate();

	void landInIt();		//new game Init
	void saveLandInIt();	//save game Init
	void landUpdate();


protected:

	typedef vector<vector<int>> double_land_array;
	typedef vector<vector<double_land_array>> double_double_land_array;

	double_land_array land_inner_grid;
	double_double_land_array land_outer_grid;
	map<unsigned, double_double_land_array> landDataBase;

private:

	unsigned landID;
};

#endif