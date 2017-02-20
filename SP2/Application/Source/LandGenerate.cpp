#include "LandGenerate.h"
//#include "ObjectFactory.h"
#include "MyMath.h"
#include "Rock.h"
#include "Tree.h"
#include <iostream>

LandGenerate::LandGenerate() {}

LandGenerate::~LandGenerate() {}

void LandGenerate::landInIt() 
{
	srand(time(NULL));
	//vector<unsigned> temp; 

	for (int z = 0; z < 5; z++)					//loops the grid in grid y/z
	{
		for (int x = 0; x < 5; x++)				//loops the grid in grid x
		{
			outer_grid[x][z] = rand() % 2 + 1;
		}					
	} 
	//randomize the objects in planet
	//-> setting object in random pos
	//-> different obj
	//->spawn location of AI
}

void LandGenerate::saveLandInIt(unsigned landID)
{

}

void LandGenerate::landUpdate()
{

	//update the land_map based on interactions
	//->mining of minerals (despawn minerals/change texture)
}

double_land_array LandGenerate::double_land_getter()
{
	return land_inner_grid;
}

vector<ObjectRender*> LandGenerate::obj_storage_getter()
{
	return obj_storage;
}

void LandGenerate::buildingLand(double_land_array land)
{

}

