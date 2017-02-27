#include "CollisionManager.h"
#include "ObjectFactory.h"
#include "Tree.h"
#include "Rock.h"

CollisionManager::CollisionManager() { collision_aabb = new Func_AABB; }

CollisionManager::~CollisionManager() 
{
	//delete collision_aabb;
	//delete this;
}

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
		Player->getCam()->cForward = collision_aabb->pointInAABB(Player->getCam()->pFront, landGen->obj_data_at_box[ID][i]->get_obj_AABB());
		if (Player->getCam()->cForward)
		{
			landGen->obj_data_at_box[ID][i]->interact();
			break;
		}
		Player->getCam()->cBack = collision_aabb->pointInAABB(Player->getCam()->pBack, landGen->obj_data_at_box[ID][i]->get_obj_AABB());
		if (Player->getCam()->cBack)
		{
			break;
		}
		Player->getCam()->cLeft = collision_aabb->pointInAABB(Player->getCam()->pLeft, landGen->obj_data_at_box[ID][i]->get_obj_AABB());
		if (Player->getCam()->cLeft)
		{
			break;
		}
		Player->getCam()->cRight = collision_aabb->pointInAABB(Player->getCam()->pRight, landGen->obj_data_at_box[ID][i]->get_obj_AABB());
		if (Player->getCam()->cRight)
		{
			break;
		}
		
	}

	ID = 0; //reset id at end
}

void CollisionManager::CollisionCheckerSystem(SolarGenerate* SolarGen, SystemTravelShip* playerShip, float sRotate)
{
	float angleRotationX, angleRotationY;
	float radiusX, radiusY, centreX, centreY;
	isAbovePlanet = false;
	Vector3 planetPos;
	//float posX, posZ;
	
	centreX = 0;
	centreY = 0;

	//radiusX = 9 * 250;
	//radiusY = 9 * 250;

	//for (int i = 0; i < SolarGen->planet_storage_getter().size(); i++)
	for (int i = 0; i < SolarGen->planet_storage_getter().size(); i++)
	{
		radiusX = 0;
		radiusY = 0;

		angleRotationX = cos(SolarGen->planet_storage_getter()[i]->aroundRotate * Math::DegreeToRadian(sRotate));
		angleRotationY = sin(SolarGen->planet_storage_getter()[i]->aroundRotate * Math::DegreeToRadian(sRotate));

		radiusX = 9 * (i + 1) * 250;
		radiusY = 9 * (i + 1) * 250;

		planetPos.x = centreX + radiusX * angleRotationX;
		planetPos.y = centreY + radiusY * angleRotationY;

		//if (Application::IsKeyPressed(VK_F11))
		//	std::cout << "playerPos: " << playerShip->position << std::endl;
		//	//std::cout << playerShip->func_aabb_getter()->getAABB().pt_Max << std::endl;
		//if (Application::IsKeyPressed(VK_F12))
		//{
		//	std::cout << "=========================" << std::endl;
		//	std::cout << playerShip->func_aabb_getter()->getAABB().pt_Min << std::endl;
		//	std::cout << "=========================" << std::endl;
		//	std::cout << playerShip->func_aabb_getter()->getAABB().pt_Max << std::endl;
		//	std::cout << "=========================" << std::endl;
		//}
		//
		//if (Application::IsKeyPressed(VK_F10))
		//{
		//	//std::cout << "A: " << planetPos << std::endl;
		//	std::cout << "-----------------" << std::endl;
		//	std::cout << collision_aabb->getAABB().pt_Max << std::endl;
		//	std::cout << "-----------------" << std::endl;
		//	std::cout << collision_aabb->getAABB().pt_Min << std::endl;
		//	std::cout << "-----------------" << std::endl;
		//}

		collision_aabb->updateAABB(280, 280, 1000, planetPos);

		if (collision_aabb->AABBtoAABB(playerShip->func_aabb_getter()->getAABB()))
		{
			planet_type = SolarGen->planet_storage_getter()[i]->type;
			isAbovePlanet = true;
			break;
		}

	}

}