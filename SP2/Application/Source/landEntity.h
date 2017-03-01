#ifndef _LAND_ENTITY_H
#define _LAND_ENTITY_H

#include "Vector3.h"

#include <string>

class LandEntity abstract
{
public:
	Vector3 getter(std::string);
	float getHealth();
	float getShield();

	void setHealth(float);
	void setShield(float);
	Vector3 Position;

	//virtual void Update(double dt) = 0;
	Vector3 getRight();
protected:

	Vector3 Forward;
	Vector3 Up;
	Vector3 Right;

	float Health;
	float Shield;
};

#endif