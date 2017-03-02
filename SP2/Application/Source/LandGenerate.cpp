#include "LandGenerate.h"

#include "MyMath.h"
#include "Rock.h"
#include "Tree.h"
#include "Mithril.h"
#include "Bismuth.h"
#include "Titanium.h"
#include "Iron.h"

#include <iostream>

LandGenerate::LandGenerate(StudioProject* scene) : myscene(scene), objectfactory(scene) 
{
	sceneID = 1;
}

LandGenerate::LandGenerate(PlanetScene* scene) : planet_scene(scene), objectfactory(scene) 
{
	sceneID = 2;
	SystemID = GalaxyGenerate::get_instance()->galaxy_id_getter();
	PlanetID = GalaxyGenerate::get_instance()->planet_id_getter();
}

LandGenerate::~LandGenerate() 
{
}

void LandGenerate::landInIt() 
{
	Vector3 tempPos;
	Vector3 enemyPos;
	float enemyGoalx = 0;
	float enemyGoalz = 0;
	tempPos.Set(0, 0, 0);
	enemyPos.Set(0, 0, 0);
	srand((time_t)(time(NULL)));				//seed
	unsigned count = 1;							//count number of grid

	//for (int i = 0; i <= 25; i++)
	//{
	//	obj_data_at_box[i].clear();
	//	std::cout << obj_data_at_box[i].size() << "\n";
	//}
	//obj_data_at_box.clear();
	//objectfactory.clearObjects();				

	//if (sceneID == 1)
	//{
	//	for (int z = 0; z < 5; z++)					//loops the grid in grid y/z
	//	{
	//		for (int x = 0; x < 5; x++)				//loops the grid in grid x
	//		{
	//			int numOfObject = Math::RandIntMinMax(10, 20);  //num of obj
	//			for (int i = 0; i < numOfObject; i++)
	//			{
	//				tempPos.x = Math::RandIntMinMax((x * 500) + 10, ((x + 1) * 500) - 10);
	//				tempPos.z = Math::RandIntMinMax((z * 500) + 10, ((z + 1) * 500) - 10);
	//				int objType = Math::RandIntMinMax(1, 2); //selecting the type of obj

	//				//=== selection of type ===================================================
	//				if (objType == 1)
	//				{
	//					//Rock* rock = new Rock(planet_scene, Vector3(tempPos.x, 0, tempPos.z), 3);
	//					objectfactory.createObject(new Rock(myscene, Vector3(tempPos.x, -2, tempPos.z), 3));
	//				}
	//				else if (objType == 2)
	//				{
	//					//Tree* tree = new Tree(planet_scene, Vector3(tempPos.x, 0, tempPos.z), 3);
	//					objectfactory.createObject(new Tree(myscene, Vector3(tempPos.x, -2, tempPos.z), 3));
	//				}
	//				//========================================================================
	//			}
	//			count++;
	//		}
	//	}
	//}
	if (sceneID == 2)
	{
		for (int z = 0; z < 5; z++)					//loops the grid in grid y/z
		{
			for (int x = 0; x < 5; x++)				//loops the grid in grid x
			{
				int numOfObject = Math::RandIntMinMax(15, 30);  //num of obj
				for (int i = 0; i < numOfObject; i++)
				{
					tempPos.x = Math::RandIntMinMax((x * 500) + 10, ((x + 1) * 500) - 10);		//rand the x pos
					tempPos.z = Math::RandIntMinMax((z * 500) + 10, ((z + 1) * 500) - 10);		//rand the y pos
					int objType = Math::RandIntMinMax(1, 29);									//selecting the type of obj

					//=== selection of type ===================================================
					if (objType >= 1 && objType <= 5)	//chances for spawning rock
					{
						Rock* rock = new Rock(planet_scene, Vector3(tempPos.x, -1, tempPos.z), 3);
						obj_data_at_box[count].push_back(rock);
						objectfactory.createObject(rock);
					}
					else if (objType > 5 && objType <= 13)	//chances for spawning tree
					{
						Tree* tree = new Tree(planet_scene, Vector3(tempPos.x, -3, tempPos.z), 3);
						obj_data_at_box[count].push_back(tree);
						objectfactory.createObject(tree);
					}
					else if (objType > 13 && objType <= 18)	 //chances for spawning mithril
					{
						Mithril* mithril = new Mithril(planet_scene, Vector3(tempPos.x, -1, tempPos.z), 3);
						obj_data_at_box[count].push_back(mithril);
						objectfactory.createObject(mithril);
					}
					else if (objType > 18 && objType <= 24)	  //chances for spawning iron
					{
						Iron* iron = new Iron(planet_scene, Vector3(tempPos.x, -1, tempPos.z), 3);
						obj_data_at_box[count].push_back(iron);
						objectfactory.createObject(iron);
					}
					else if (objType > 24 && objType <= 27)	  //chances for spawning titanium
					{
						Titanium* titanium = new Titanium(planet_scene, Vector3(tempPos.x, -1, tempPos.z), 3);
						obj_data_at_box[count].push_back(titanium);
						objectfactory.createObject(titanium);
					}
					else if (objType > 27 && objType <= 29)	  //chances for spawning bismuth
					{
						Bismuth* bismuth = new Bismuth(planet_scene, Vector3(tempPos.x, -1, tempPos.z), 3);
						obj_data_at_box[count].push_back(bismuth);
						objectfactory.createObject(bismuth);
					}
					//========================================================================
				}
				count++;  //increase the count which represents the grid
			}
		}

		//random enemy generation

		for (int z = 0; z < 5; z++)					//loops the grid in grid y/z
		{
			for (int x = 0; x < 5; x++)				//loops the grid in grid x
			{
				noOfEnemies = Math::RandIntMinMax(3, 7);  //num of enemies
				for (int i = 0; i < noOfEnemies; i++)
				{
					enemyPos.x = Math::RandIntMinMax((x * 300) + 100, ((x + 1) * 700) - 100);
					enemyPos.z = Math::RandIntMinMax((z * 300) + 100, ((z + 1) * 700) - 100);
					enemyGoalx = Math::RandIntMinMax(50, 150);
					enemyGoalz = Math::RandIntMinMax(50, 150);
					int enemyType = Math::RandIntMinMax(1, 2); //selecting the type of enemy

					//=== selection of type ===================================================
					if (enemyType == 1)
					{
						enemy_positions.push_back(Vector3(enemyPos.x, 0, enemyPos.z));
						enemy_goal.push_back(Vector3(enemyPos.x + enemyGoalx, enemyPos.z + enemyGoalz));
						enemy_type.push_back(1);
					}
					else if (enemyType == 2)
					{
						enemy_positions.push_back(Vector3(enemyPos.x, 0, enemyPos.z));
						enemy_goal.push_back(Vector3(enemyPos.x + enemyGoalx, enemyPos.z + enemyGoalz));
						enemy_type.push_back(2);
					}
					//========================================================================
				}
				count++;  //increase the count which represents the grid
			}
		}

	}

	SetPath();		//fills up a 2d array to show which part is empty and which are being used
}

void LandGenerate::saveLandInIt()
{
	PlanetID = GalaxyGenerate::get_instance()->planet_id_getter();
	GalaxyGenerate::get_instance()->system_database[SystemID]->land_database[PlanetID] = this;
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
	//objectfactory.renderObjects(sceneID);
	//GalaxyGenerate::get_instance()->system_database[SystemID]->land_database[SystemID][PlanetID]->objectfactory.renderObjects(2);
	GalaxyGenerate::get_instance()->system_database[SystemID]->land_database[PlanetID]->objectfactory.renderObjects(2);
}

void LandGenerate::SetPath()
{
	int rangeX, rangeZ;				//range of the AABB box
	int PointX, PointZ;				//the different point in the range of box

	for (int i = 0; i < 2500; i++)		//loop throught the 2d array
	{
		for (int j = 0; j < 2500; j++)
		{
			path[i][j] = '-';			//set it all to '-' which represent empty
		}
	}

	for (int i = 0; i < obj_data_at_box.size(); i++)			//loop through map[id]
	{
		for (int j = 0; j < obj_data_at_box[i].size(); i++)		//loop through objs stored in that map[id]
		{
			rangeX = (int)(obj_data_at_box[i][j]->get_obj_AABB().pt_Max.x - obj_data_at_box[i][j]->get_obj_AABB().pt_Min.x);	//find range of box for x axis
			rangeZ = (int)(obj_data_at_box[i][j]->get_obj_AABB().pt_Max.z - obj_data_at_box[i][j]->get_obj_AABB().pt_Min.z);	//find range of box for z axis

			PointX = (int)(obj_data_at_box[i][j]->get_obj_AABB().pt_Min.x);		//set min point for x
			PointZ = (int)(obj_data_at_box[i][j]->get_obj_AABB().pt_Min.z);		//set min point for z

			for (int z = 0; z < rangeZ; z++)				//loop through the z range
			{
				PointZ += 1;								//increase the point z of the range
				for (int x = 0; x < rangeX; x++)			//loop through the x range
				{
					path[PointX][PointZ] = 'F';				//set it to 'F' to represent it is occupied
					PointX += 1;							//increase the point x of the range
				}
				PointX = 0;									//reset after loop
			}
			PointZ = 0;										//reset after loop

		}
	}
}

int LandGenerate::planet_id_getter()
{
	return PlanetID;
}