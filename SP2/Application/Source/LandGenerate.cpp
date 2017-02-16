#include "LandGenerate.h"
#include <iostream>

LandGenerate::LandGenerate() : landID(0) {}

LandGenerate::~LandGenerate() {}

void LandGenerate::landInIt() 
{
	//1st[]-Bigger_Grid_Y(Z)  2nd[]-Bigger_Grid_X   3rd[]-Inner_Grid_Y(Z)   4th[]-Inner_Grid_X (REFERENCE THIS PLS)

	srand(time(NULL));

	//vector<LandGenerate*> temp; 

	//for (int outerY = 0; outerY < 10; outerY++)		//loops the big grid y/z
	//{
	//	for (int outerX = 0; outerX < 10; outerX++)		//loops the big grid x
	//	{
	//		for (int y = 0; y < 50; y++)				//loops the grid in grid y/z
	//		{
	//			for (int x = 0; x < 50; x++)			//loops the grid in grid x
	//			{
	//				temp.push_back(rand() % 10 + 1);	//this is a vector (sets pos(x) of the smaller grid to this random value)
	//			}

	//			land_inner_grid.push_back(temp);		//this is a vector vector (sets pos(z) of the smaller grid to this random value)
	//			temp.clear();							//clears prev vector data
	//		} 

	//		tempStore.push_back(land_inner_grid);		//this is a vector vector vector (sets pos(x) of the bigger grid to this smaller grid)
	//		land_inner_grid.clear();					//clears prev vector data
	//	}

	//	land_outer_grid.push_back(tempStore);			//this is a vector vector vector vector (sets pos(z) of the bigger grid to this smaller grid)
	//	tempStore.clear();								//clears prev vector data
	//}
	//

	//landDataBase.push_back(land_outer_grid);			//push back this to database
	//this->landID++;

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

//double_double_land_array LandGenerate::getter()
//{
//	//return land_outer_grid;
//}
//
//void LandGenerate::buildingLand(double_double_land_array land)
//{
//
//}