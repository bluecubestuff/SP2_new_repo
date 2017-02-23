#include "GreenPlanet.h"

GreenPlanet::GreenPlanet(SystemScene* scene, Vector3 pos, float sizeX, float sizeZ, float aRotate, float pRotate)
	: ObjectRender(scene, pos, sizeX, sizeZ, aRotate, pRotate)
{
	aabb = new Func_AABB;

	type = SystemScene::GEO_SUN;
}

GreenPlanet::~GreenPlanet() {}

void GreenPlanet::interact()
{

}

AABB GreenPlanet::get_obj_AABB()
{
	return green_planet_box;
}