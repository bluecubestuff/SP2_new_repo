#ifndef _COLLISION_MANAGER_H
#define _COLLISION_MANAGER_H

#include "Camera.h"
#include "Func_AABB.h"
#include "LandGenerate.h"
#include "SolarGenerate.h"
#include "landPlayer.h"
#include "SystemTravelShip.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void CollisionChecker(LandGenerate*, LandPlayer*);
	void CollisionCheckerSystem(SolarGenerate*, SystemTravelShip*,float);

	bool isAbovePlanet;
	unsigned planet_typing = 0;
private:
	Func_AABB* collision_aabb;
};

#endif