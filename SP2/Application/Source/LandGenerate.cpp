#include "LandGenerate.h"
//#include "ObjectFactory.h"
#include "MyMath.h"
#include "Rock.h"
#include "Tree.h"
#include <iostream>

LandGenerate::LandGenerate(StudioProject* scene) : myscene(scene), objectfactory(scene) 
{
	sceneID = 1;
}

LandGenerate::LandGenerate(PlanetScene* scene) : planet_scene(scene), objectfactory(scene) 
{
	sceneID = 2;
}

LandGenerate::~LandGenerate() {}

void LandGenerate::landInIt() 
{
	Vector3 tempPos;
	tempPos.Set(0, 0, 0);			
	srand((time_t)(time(NULL)));				//seed
	unsigned count = 1;							//count number of grid

	obj_data_at_box.clear();
	objectfactory.clearObjects();				//clears the vector when reInit (change scenes)

	if (sceneID == 1)
	{
		for (int z = 0; z < 5; z++)					//loops the grid in grid y/z
		{
			for (int x = 0; x < 5; x++)				//loops the grid in grid x
			{
				int numOfObject = Math::RandIntMinMax(10, 20);  //num of obj
				for (int i = 0; i < numOfObject; i++)
				{
					tempPos.x = Math::RandIntMinMax((x * 500) + 10, ((x + 1) * 500) - 10);
					tempPos.z = Math::RandIntMinMax((z * 500) + 10, ((z + 1) * 500) - 10);
					int objType = Math::RandIntMinMax(1, 2); //selecting the type of obj

					//=== selection of type ===================================================
					if (objType == 1)
					{
						//Rock* rock = new Rock(planet_scene, Vector3(tempPos.x, 0, tempPos.z), 3);
						objectfactory.createObject(new Rock(myscene, Vector3(tempPos.x, 0, tempPos.z), 3));
					}
					else if (objType == 2)
					{
						//Tree* tree = new Tree(planet_scene, Vector3(tempPos.x, 0, tempPos.z), 3);
						objectfactory.createObject(new Tree(myscene, Vector3(tempPos.x, 0, tempPos.z), 3));
					}
					//========================================================================
				}
				count++;
			}
		}
	}
	else if (sceneID == 2)
	{
		for (int z = 0; z < 5; z++)					//loops the grid in grid y/z
		{
			for (int x = 0; x < 5; x++)				//loops the grid in grid x
			{
				int numOfObject = Math::RandIntMinMax(10, 20);  //num of obj
				for (int i = 0; i < numOfObject; i++)
				{
					tempPos.x = Math::RandIntMinMax((x * 500) + 10, ((x + 1) * 500) - 10);
					tempPos.z = Math::RandIntMinMax((z * 500) + 10, ((z + 1) * 500) - 10);
					int objType = Math::RandIntMinMax(1, 2); //selecting the type of obj

					//=== selection of type ===================================================
					if (objType == 1)
					{
						Rock* rock = new Rock(planet_scene, Vector3(tempPos.x, 0, tempPos.z), 3);
						obj_data_at_box[count].push_back(rock);
						objectfactory.createObject(rock);
					}
					else if (objType == 2)
					{
						Tree* tree = new Tree(planet_scene, Vector3(tempPos.x, 0, tempPos.z), 3);
						obj_data_at_box[count].push_back(tree);
						objectfactory.createObject(tree);
					}
					//========================================================================
				}
				count++;
			}
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

ObjectFactory LandGenerate::object_factory_getter()
{
	return this->objectfactory;
}

void LandGenerate::BuildLand()
{
	objectfactory.renderObjects(sceneID);
}

