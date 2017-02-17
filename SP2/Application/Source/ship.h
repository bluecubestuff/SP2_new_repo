#ifndef _SHIP_H
#define _SHIP_H

#include <vector>

#include "Application.h"
#include "Vector3.h"
#include "Mtx44.h"
#include "Camera2.h"
#include "func_AABB.h"
#include "DetectMemoryLeak.h"

using std::vector;

class Ship abstract
{
public:
	Ship();
	Ship(Vector3 f, Vector3 u, Vector3 r, Vector3 p, Vector3 i, float size, float hullPoints, float maxShield, float mass, float thrust, float turnSpeed);
	~Ship();

	bool locked;

	Vector3 getter(std::string);
	AABB getAABB();
	Mtx44 getStamp();
private:

protected:
	Vector3 Forward;
	Vector3 Up;
	Vector3 Right;
	Vector3 Position;
	Vector3 Inertia;

	float size;
	float hullPoints;
	float maxShield;
	float mass;
	float thrust;
	float turnSpeed;

	Func_AABB* hitbox;

	Mtx44 Stamp;
};

#endif