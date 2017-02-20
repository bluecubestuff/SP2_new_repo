#include "LandGenerate.h"
//#include "ObjectFactory.h"
#include "MyMath.h"
#include "Rock.h"
#include "Tree.h"
#include <iostream>

LandGenerate::LandGenerate(StudioProject* scene) : myscene(scene), objectfactory(scene)
{

}

LandGenerate::~LandGenerate() {}

void LandGenerate::landInIt() 
{
	Vector3 tempPos;
	tempPos.Set(0, 0, 0);
	int counter = 0;
	srand(time(NULL));

	for (int z = 0; z < 5; z++)					//loops the grid in grid y/z
	{
		for (int x = 0; x < 5; x++)				//loops the grid in grid x
		{
			int numOfObject = (rand() % 10 + 1);
			for (int i = 0; i < numOfObject; i++)
			{
				tempPos.x = Math::RandIntMinMax(x * 500, (x + 1) * 500);
				tempPos.z = Math::RandIntMinMax(z * 500, (z + 1) * 500);
				int objType = Math::RandIntMinMax(1, 2);
				if (objType == 1)
					objectfactory.createObject(new Rock(myscene, Vector3(tempPos.x, 0, tempPos.z), 3));
				else if (objType == 2)
					objectfactory.createObject(new Tree(myscene, Vector3(tempPos.x, 0, tempPos.z), 3));
			}
			counter++;
		}
	}

	std::cout << "objectfactory container" << objectfactory.objContainer.size();
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

//ObjectFactory LandGenerate::object_factory_getter()
//{
//	return objectfactory;
//}

void LandGenerate::BuildLand()
{
	objectfactory.renderObjects();
}

