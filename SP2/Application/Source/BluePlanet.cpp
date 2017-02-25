#include "BluePlanet.h"

BluePlanet::BluePlanet(SystemScene* scene, Vector3 pos, float sizeX, float sizeY, float aRotate, float pRotate)
	: ObjectRender(scene, pos, sizeX, sizeY, aRotate, pRotate)
{
	aabb = new Func_AABB;

	type = SystemScene::GEO_BLUEPLANET;
	Vector3 sunPos;
	sunPos.Set(1000, 1000, 1000); //(1000,6000,1000)
	sunPos += pos;

	aabb->setAABB_Static_Objects(sunPos, 250 * sizeX, 250 * sizeY, 250 * sizeY);
	green_planet_box = aabb->getAABB();

	std::cout << green_planet_box.pt_Min << "\n";
	std::cout << green_planet_box.pt_Max << "\n";
}

BluePlanet::~BluePlanet() {}

void BluePlanet::interact()
{

}

AABB BluePlanet::get_obj_AABB()
{
	return green_planet_box;
}