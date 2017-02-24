#include "Rock.h"

Rock::Rock(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	aabb = new Func_AABB;
	type = StudioProject::GEO_ROCK;
	aabb->setAABB_Static_Objects(pos, size, size, size);
	Rock_box = aabb->getAABB();
}
Rock::Rock(PlanetScene* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	aabb = new Func_AABB;
	type = PlanetScene::GEO_ROCK;
	aabb->setAABB_Static_Objects(pos, size + 2, size + 5, size + 2);
	Rock_box = aabb->getAABB();
}
void Rock::interact()
{
	if (Application::IsKeyPressed('C'))
	{
		type = PlanetScene::GEO_GOATGOAT;
	}
}
AABB Rock::get_obj_AABB()
{
	return Rock_box;
}