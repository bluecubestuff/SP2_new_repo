#ifndef _LAND_GENERATE_H
#define _LAND_GENERATE_H

#include "GalaxyGenerate.h"
#include "Vector3.h"
#include "Randomise.h"

typedef vector<vector<int>> double_land_array;
typedef vector<vector<double_land_array>> double_double_land_array;

class LandGenerate
{
public:

	LandGenerate();
	~LandGenerate();

	void landInIt();				//newInit
	void saveLandInIt(unsigned);	//reloadInit
<<<<<<< HEAD
	void landUpdate();
	void buildingLand(double_double_land_array);

	double_double_land_array getter();

protected:
	double_land_array land_inner_grid;
	double_double_land_array land_outer_grid;
	
	vector<double_land_array> tempStore;
	vector<double_double_land_array> landDataBase;

private:
=======
	void landUpdate();             
	double_land_array getter();

	double_land_array land_inner_grid;
	int outer_grid[10][10];

private:

>>>>>>> f64aec40b4df18743c47ba3a882a48d63295a107
	unsigned landID;
	//ObjectFactory* tester;

};

#endif