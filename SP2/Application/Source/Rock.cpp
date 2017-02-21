#include "Rock.h"

Rock::Rock(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	aabb = new Func_AABB;
	type = StudioProject::GEO_ROCK;
	aabb->setAABB_Static_Objects(pos, size);
	Rock_box = aabb->getAABB();
}
void Rock::interact()
{

}
AABB Rock::get_obj_AABB()
{
	return Rock_box;
}