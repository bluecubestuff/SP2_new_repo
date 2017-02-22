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

LandGenerate::~LandGenerate() 
{
}

void LandGenerate::landInIt() 
{
	Vector3 tempPos;
	tempPos.Set(0, 0, 0);			
	srand((time_t)(time(NULL)));				//seed
	unsigned count = 1;							//count number of grid

	//for (int i = 0; i <= 25; i++)
	//{
	//	obj_data_at_box[i].clear();
	//	std::cout << obj_data_at_box[i].size() << "\n";
	//}
	//obj_data_at_box.clear();
	//objectfactory.clearObjects();				//clears the vector when reInit (change scenes)

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
						objectfactory.createObject(new Rock(myscene, Vector3(tempPos.x, -2, tempPos.z), 3));
					}
					else if (objType == 2)
					{
						//Tree* tree = new Tree(planet_scene, Vector3(tempPos.x, 0, tempPos.z), 3);
						objectfactory.createObject(new Tree(myscene, Vector3(tempPos.x, -2, tempPos.z), 3));
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
						Rock* rock = new Rock(planet_scene, Vector3(tempPos.x, -1, tempPos.z), 3);
						obj_data_at_box[count].push_back(rock);
						objectfactory.createObject(rock);
					}
					else if (objType == 2)
					{
						Tree* tree = new Tree(planet_scene, Vector3(tempPos.x, -3, tempPos.z), 3);
						obj_data_at_box[count].push_back(tree);
						objectfactory.createObject(tree);
					}
					//========================================================================
				}
				count++;  //increase the count which represents the grid
			}
		}
	}

	SetPath();

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

void LandGenerate::SetPath()
{
	int rangeX, rangeZ;
	int minPointX, minPointZ;

	for (int i = 0; i < obj_data_at_box.size(); i++) //loop through map[id]
	{
		for (int j = 0; j < obj_data_at_box[i].size(); i++) //loop through objs stored in that map[id]
		{
			rangeX = (int)(obj_data_at_box[i][j]->get_obj_AABB().pt_Max.x - obj_data_at_box[i][j]->get_obj_AABB().pt_Min.x); //find range of box for x axis
			rangeZ = (int)(obj_data_at_box[i][j]->get_obj_AABB().pt_Max.z - obj_data_at_box[i][j]->get_obj_AABB().pt_Min.z); //find range of box for z axis

			minPointX = (int)(obj_data_at_box[i][j]->get_obj_AABB().pt_Min.x);
			minPointZ = (int)(obj_data_at_box[i][j]->get_obj_AABB().pt_Min.z);

			for (int z = 0; z < rangeZ; z++)
			{
				minPointZ += 1;
				for (int x = 0; x < rangeX; x++)
				{
					path[minPointX][minPointZ] = 'F';
					minPointX += 1;
				}
				minPointX = 0; //reset after loop
			}
			minPointZ = 0; //reset after loop

		}
	}

	int counta = 0;
	for (int i = 0; i < 2500; i++)
	{
		for (int j = 0; j < 2500; j++)
		{
			if (path[i][j] == 'F')
			{
				counta++;
			}
		}
	}

	std::cout << counta << "\n";
}