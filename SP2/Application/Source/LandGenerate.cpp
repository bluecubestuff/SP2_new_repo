#include "LandGenerate.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include <iostream>

LandGenerate::LandGenerate() : landID(0) {}

LandGenerate::~LandGenerate() {}

void LandGenerate::landInIt()
{
	vector<int> temp;
	
	for (int y = 0; y <= 100; y++) 
	{
		for (int x = 0; x <= 100; x++)
		{
			temp.push_back(x); //2nd vector push_back
		}
		land_inner_grid.push_back(temp); //1st vector push_back
	}

	vector<double_land_array> temp2;

	for (int outerY = 0; outerY < 10; outerY++)
	{
		for (int outerX = 0; outerX < 10; outerX++)
		{
			temp2.push_back(land_inner_grid);//x
		}
		land_outer_grid.push_back(temp2); //y
	}
	
	std::cout << land_outer_grid[1][1][50][100]; // 1st[]-Bigger_Grid_Y(Z)  2nd[]-Bigger_Grid_X   3rd[]-Inner_Grid_Y(Z)   4th[]-Inner_Grid_X
	


	//landDataBase[landID] = land_outer_grid;
	//landID++;
	//randomize the objects in planet
	//-> setting object in random pos
	//-> different obj
	//->spawn location of AI
}

void LandGenerate::saveLandInIt()
{

}

void LandGenerate::landUpdate()
{






	//update the land_map based on interactions
	//->mining of minerals (despawn minerals/change texture)
}