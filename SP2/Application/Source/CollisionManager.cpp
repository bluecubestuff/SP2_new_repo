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
			landGen->obj_data_at_box[ID][i]->interact();//interact with obj
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
	
	centreX = 0;
	centreY = 0;

	//radiusX = 9 * 250;
	//radiusY = 9 * 250;

	for (int i = 0; i < SolarGen->planet_storage_getter().size(); i++)
	{
		radiusX = 0;
		radiusY = 0;

		angleRotationX = cos(SolarGen->planet_storage_getter()[i]->aroundRotate * Math::DegreeToRadian(sRotate));
		angleRotationY = sin(SolarGen->planet_storage_getter()[i]->aroundRotate * Math::DegreeToRadian(sRotate));

		radiusX = 9 * (i + 1) * 250;
		radiusY = 9 * (i + 1) * 250;

		planetPos.x = centreX + radiusX * angleRotationX;		//find the x pos while planet rotates
		planetPos.y = centreY + radiusY * angleRotationY;		//fint the y pos while planet rotates	

		collision_aabb->updateAABB(280, 280, 1000, planetPos);	//updates the collision of the planets
	
		if (collision_aabb->AABBtoAABB(playerShip->func_aabb_getter()->getAABB()))	//check to see if player ship is in planets AABB
		{
			planet_typing = SolarGen->planet_storage_getter()[i]->objID;				//set the planet type
			isAbovePlanet = true;
			GalaxyGenerate::get_instance()->set_planet_id(i + 1);					//set the id of which planet player is going to land at
			break;
		}

	}

}
