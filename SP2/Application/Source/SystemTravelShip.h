#ifndef _SYSTEM_TRAVEL_SHIP_H
#define _SYSTEM_TRAVEL_SHIP_H

#include "Func_AABB.h"
#include "Vector3.h"

class SystemTravelShip
{
public:
	SystemTravelShip();
	~SystemTravelShip();

	Vector3 position;
	Vector3 forward;

	float rotate;

	void Update(double);

	Func_AABB* func_aabb_getter();

private:
	Func_AABB* func_aabb;
};

#endif