#ifndef _COLLISION_MANAGER_H
#define _COLLISION_MANAGER_H

#include "Camera.h"
#include "Func_AABB.h"
#include "LandGenerate.h"


class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void CollisionChecker(LandGenerate*,Camera);
private:
	Func_AABB* aabb;
};

#endif