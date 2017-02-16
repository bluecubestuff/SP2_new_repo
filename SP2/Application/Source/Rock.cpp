#include "Rock.h"

Rock::Rock(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	type = StudioProject::GEO_ROCK;
	aabb->setAABB_Static_Objects(pos, size);
}
void Rock::interact()
{

}