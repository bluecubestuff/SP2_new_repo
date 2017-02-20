#ifndef _LAND_GENERATE_H
#define _LAND_GENERATE_H

#include "GalaxyGenerate.h"
#include "Vector3.h"
#include "Randomise.h"
#include "ObjectRender.h"

typedef vector<vector<unsigned>> double_land_array;

class LandGenerate
{
public:
	LandGenerate();
	~LandGenerate();

	void landInIt();				//newInit
	void saveLandInIt(unsigned);	//reloadInit
	void landUpdate();
	void buildingLand(double_land_array);
	double_land_array double_land_getter();
	vector<ObjectRender*> obj_storage_getter();

	int outer_grid[5][5];

private:
	double_land_array land_inner_grid;
	vector<ObjectRender*> obj_storage;
	Vector3 obj_pos;
private:
	StudioProject* myscene;
};

#endif