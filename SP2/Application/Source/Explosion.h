#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include "Vector3.h"

//no particles

class Explosion
{
public:
	Explosion();
	Explosion(Vector3);
	~Explosion();

	void Update(double);
	bool getDone();
	Vector3 getPos();
	float getScale();
private:
	float bufferTime;
	float scaling;

	bool done;

	Vector3 Position;
};

#endif