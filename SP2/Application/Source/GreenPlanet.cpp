#include "GreenPlanet.h"

GreenPlanet::GreenPlanet(SystemScene* scene, Vector3 pos, float sizeX, float sizeY, float aRotate, float pRotate)
	: ObjectRender(scene, pos, sizeX, sizeY, aRotate, pRotate)
{
	aabb = new Func_AABB;

	type = SystemScene::GEO_GREENPLANET;
	Vector3 sunPos;
	sunPos.Set(1000, 1000, 1000); //(1000,6000,1000)
	sunPos += pos;

	aabb->setAABB_Static_Objects(sunPos, 250 * sizeX, 250 * sizeY, 250 * sizeY);
	green_planet_box = aabb->getAABB();

	objID = 1;
}

GreenPlanet::~GreenPlanet() {}

void GreenPlanet::interact()
{

}

AABB GreenPlanet::get_obj_AABB()
{
	return green_planet_box;
}