#include "Sun.h"

Sun::Sun(GalaxyScene* scene, Vector3 pos, float sizeX, float sizeY, float aRotate, float pRotate)
	: ObjectRender(scene, pos, sizeX, sizeY, aRotate, pRotate)
{
	aabb = new Func_AABB;

	type = GalaxyScene::GEO_SUN;
	Vector3 sunPos;
	sunPos.Set(1000, 1000, 1000); //(1000,6000,1000)
	sunPos += pos;

	aabb->setAABB_Static_Objects(sunPos, 250 * sizeX, 250 * sizeY, 250 * sizeY);
	sun_box = aabb->getAABB();

	std::cout << sun_box.pt_Min << "\n";
	std::cout << sun_box.pt_Max << "\n";
}

Sun::~Sun() {}

void Sun::interact()
{

}

AABB Sun::get_obj_AABB()
{
	return sun_box;
}