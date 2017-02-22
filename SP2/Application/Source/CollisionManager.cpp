#include "CollisionManager.h"
#include "ObjectFactory.h"
#include "Tree.h"
#include "Rock.h"

CollisionManager::CollisionManager() { aabb = new Func_AABB; }

CollisionManager::~CollisionManager() {}

void CollisionManager::CollisionChecker(LandGenerate* landGen, LandPlayer* PlayerPos)
{	
	int ID = 1;

	for (int z = 0; z < 5; z++)					//loops the grid in grid y/z
	{
		for (int x = 0; x < 5; x++)				//loops the grid in grid x
		{
			if (PlayerPos->getter("position").x < ((x + 1) * 500) && PlayerPos->getter("position").x >(x * 500) &&
				PlayerPos->getter("position").z <((z + 1) * 500) && PlayerPos->getter("position").z > (z * 500))
			{	//check if player is within
				break;
			}
			ID++;
		}
		if (PlayerPos->getter("position").z <((z + 1) * 500) && PlayerPos->getter("position").z  >(z * 500))
		{
			break;
		}
		
	}

	for (int i = 0; i < landGen->obj_data_at_box[ID].size(); i++)
	{
		landGen->obj_data_at_box[ID][i]->get_obj_AABB();
		//std::cout << landGen->obj_data_at_box[ID][i]->get_obj_AABB().pt_Max << "\n";
		if (aabb->pointInAABB(PlayerPos->getter("position"), landGen->obj_data_at_box[ID][i]->get_obj_AABB()))
		{
			std::cout << "in box: " << "\n";
		}
	}

	ID = 0; //reset id at end
}