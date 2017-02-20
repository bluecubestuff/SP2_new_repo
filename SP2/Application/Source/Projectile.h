#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "Vector3.h"

class Projectile abstract
{
public:
	Vector3 getPos();
protected:
	Vector3 Position;
	Vector3 Forward;
	Vector3 Right;
	Vector3 Up;
	float turnSpeed;
};

#endif