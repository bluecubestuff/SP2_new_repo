#ifndef _SYSTEM_TRAVEL_SHIP_H
#define _SYSTEM_TRAVEL_SHIP_H

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
};

#endif