#ifndef _COLLISION_MANAGER_H
#define _COLLISION_MANAGER_H

#include "ObjectFactory.h"
#include "LandGenerate.h"
#include "Tree.h"
#include "Rock.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void CollisionChecker(ObjectFactory);
private:
};

#endif