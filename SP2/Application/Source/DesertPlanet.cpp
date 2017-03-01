#include "DesertPlanet.h"

DesertPlanet::DesertPlanet(SystemScene* scene, Vector3 pos, float sizeX, float sizeY, float aRotate, float pRotate)
	: ObjectRender(scene, pos, sizeX, sizeY, aRotate, pRotate)
{
	aabb = new Func_AABB;

	type = SystemScene::GEO_DESERTPLANET;
	Vector3 sunPos;
	sunPos.Set(1000, 1000, 1000); //(1000,6000,1000)
	sunPos += pos;

	aabb->setAABB_Static_Objects(sunPos, 250 * sizeX, 250 * sizeY, 250 * sizeY);
	green_planet_box = aabb->getAABB();

	objID = 2;
}

DesertPlanet::~DesertPlanet() {}

void DesertPlanet::interact()
{

}

AABB DesertPlanet::get_obj_AABB()
{
	return green_planet_box;
}