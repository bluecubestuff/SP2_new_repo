#ifndef _LAND_VEHICLE_H
#define _LAND_VEHICLE_H

#include "landEntity.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Func_AABB.h"
#include "Application.h"

class LandVehicle : public LandEntity
{
public:
	LandVehicle();
	~LandVehicle();

	void Update(double);

	bool getInVehicle();
	void setInVehicle(bool);
	
	Camera3* Camera;

	Mtx44 Stamp;
	Func_AABB* hitbox;
	Func_AABB* interactionBox;
private:
	bool inVehicle;
};

#endif