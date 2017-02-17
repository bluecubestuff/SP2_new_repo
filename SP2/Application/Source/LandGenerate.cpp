#include "LandGenerate.h"
#include <iostream>
#include "ObjectRender.h"

LandGenerate::LandGenerate() : landID(0) {}

LandGenerate::~LandGenerate() {}

void LandGenerate::landInIt() 
{
	//1st[]-Bigger_Grid_Y(Z)  2nd[]-Bigger_Grid_X   3rd[]-Inner_Grid_Y(Z)   4th[]-Inner_Grid_X (REFERENCE THIS PLS)

	srand(time(NULL));

	vector<unsigned> temp;

	for (int y = 0; y < 100; y++)				//loops the grid in grid y/z
	{
		for (int x = 0; x < 100; x++)			//loops the grid in grid x
		{
			temp.push_back(rand() % 2 + 1);	//this is a vector (sets pos(x) of the smaller grid to this random value)
		}

		land_inner_grid.push_back(temp);		//this is a vector vector (sets pos(z) of the smaller grid to this random value)
		temp.clear();							//clears prev vector data
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

double_land_array LandGenerate::getter()
{
	return land_inner_grid;
}
