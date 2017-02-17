#include "Building.h"

Building::Building()
{
}

Building::~Building()
{
}

void Building::set_building_AABB(Vector3 loc,float bSize)
{
	Func_AABB* temp = new Func_AABB;
	temp->setAABB_Static_Objects(loc, bSize);
	building_AABB.push_back(temp);
}

