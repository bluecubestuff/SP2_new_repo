#include "CollisionManager.h"
#include "ObjectFactory.h"
#include "Tree.h"
#include "Rock.h"

CollisionManager::CollisionManager() { func_aabb = new Func_AABB; }

CollisionManager::~CollisionManager() {}

void CollisionManager::CollisionChecker(LandGenerate* landGen, LandPlayer* Player)
{	
	int ID = 1;

	for (int z = 0; z < 5; z++)					//loops the grid in grid y/z
	{
		for (int x = 0; x < 5; x++)				//loops the grid in grid x
		{
			if (Player->getter("position").x < ((x + 1) * 500) && Player->getter("position").x >(x * 500) &&
				Player->getter("position").z <((z + 1) * 500) && Player->getter("position").z >(z * 500))
			{									//check if player is within grid
				break;
			}
			ID++;
		}
		if (Player->getter("position").z <((z + 1) * 500) && Player->getter("position").z  >(z * 500))
		{
			break;
		}
		
	}

	for (int i = 0; i < landGen->obj_data_at_box[ID].size(); i++)
	{
		//landGen->obj_data_at_box[ID][i]->get_obj_AABB();
		//for (auto &a : landGen->obj_data_at_box[ID])
		//{ }
		Player->getCam()->cForward = func_aabb->pointInAABB(Player->getCam()->pFront, landGen->obj_data_at_box[ID][i]->get_obj_AABB());
		if (Player->getCam()->cForward)
		{
			break;
		}
		Player->getCam()->cBack = func_aabb->pointInAABB(Player->getCam()->pBack, landGen->obj_data_at_box[ID][i]->get_obj_AABB());
		if (Player->getCam()->cBack)
		{
			break;
		}
		Player->getCam()->cLeft = func_aabb->pointInAABB(Player->getCam()->pLeft, landGen->obj_data_at_box[ID][i]->get_obj_AABB());
		if (Player->getCam()->cLeft)
		{
			break;
		}
		Player->getCam()->cRight = func_aabb->pointInAABB(Player->getCam()->pRight, landGen->obj_data_at_box[ID][i]->get_obj_AABB());
		if (Player->getCam()->cRight)
		{
			break;
		}
		
		//if (cForward)
		//{
		//	std::cout << "front in box" << "\n";
		//}
		//if (func_aabb->pointInAABB(Player->getter("position"), landGen->obj_data_at_box[ID][i]->get_obj_AABB()))
		//{
		//	std::cout << "in box" << "\n";
		//}
	}

	ID = 0; //reset id at end
}