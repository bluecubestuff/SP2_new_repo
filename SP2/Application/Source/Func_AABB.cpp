#include "Func_AABB.h"

Func_AABB::Func_AABB() {}

Func_AABB::~Func_AABB() {}

bool Func_AABB::AABBtoAABB(const AABB& box01, const AABB& box02)
{
	if (box01.pt_Max.x > box02.pt_Min.x && box01.pt_Min.x < box02.pt_Max.x &&
	box01.pt_Max.y > box02.pt_Min.y && box01.pt_Min.y < box02.pt_Max.y &&
	box01.pt_Max.z < box02.pt_Min.z && box01.pt_Min.z > box02.pt_Max.z)
	{
		return true;
	}
	
	return false;
}

bool Func_AABB::pointInAABB(const AABB& box, const Vector3& point)
{
	if ((point.x > box.pt_Min.x && point.x < box.pt_Max.x)
	&& (point.z < box.pt_Min.z && point.z > box.pt_Max.z))
	{
		return true;
	}
	
	return false;
}

void Func_AABB::setAABB_Static_Objects(Vector3 location , float box_size)
{
	TAABB.pt_Max = location * box_size;
	TAABB.pt_Min = location - TAABB.pt_Max;

	AABB_Storage.push_back(TAABB);
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