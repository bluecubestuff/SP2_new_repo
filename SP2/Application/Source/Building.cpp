#include "Building.h"

Building::Building(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	type = StudioProject::GEO_BUILDING;
	aabb->setAABB_Static_Objects(pos, size, size, size);
}
void Building::interact()
{

}