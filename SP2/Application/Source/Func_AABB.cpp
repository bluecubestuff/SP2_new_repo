#include "Func_AABB.h"

Func_AABB::Func_AABB() {}

Func_AABB::~Func_AABB() 
{
	delete this;
}

bool Func_AABB::AABBtoAABB(const AABB& box01)
{
	if (box01.pt_Max.x > TAABB.pt_Min.x && box01.pt_Min.x < TAABB.pt_Max.x &&
		box01.pt_Max.y > TAABB.pt_Min.y && box01.pt_Min.y < TAABB.pt_Max.y &&
		box01.pt_Max.z > TAABB.pt_Min.z && box01.pt_Min.z < TAABB.pt_Max.z)
	{
		return true;
	}
	
	return false;
}

bool Func_AABB::pointInAABB(const Vector3& point)
{
	if ((point.x > TAABB.pt_Min.x && point.x < TAABB.pt_Max.x)
		&& (point.z > TAABB.pt_Min.z && point.z < TAABB.pt_Max.z))
	{
		return true;
	}
	
	return false;
}

void Func_AABB::setAABB_Static_Objects(Vector3 location , float box_size)
{
	TAABB.pt_Max = location + box_size;
	TAABB.pt_Min = location - box_size;
	//AABB_Storage.push_back(TAABB);
}

void Func_AABB::updateAABB(float sizeX, float sizeY, float sizeZ, Vector3 position)
{
	Vector3 temp(sizeX, sizeY, sizeZ);
	TAABB.pt_Max = position + temp;
	TAABB.pt_Min = position - temp;
}

AABB Func_AABB::getAABB()
{
	return TAABB;
}

