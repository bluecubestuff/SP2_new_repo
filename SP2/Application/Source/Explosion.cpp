#include "Explosion.h"

Explosion::Explosion()
{
	bufferTime = 0;
	Position.Set(0, 0, 0);
	done = false;
	scaling = 1;
}

Explosion::Explosion(Vector3 pos)
{
	bufferTime = 0;
	done = false;
	Position = pos;
	scaling = 1;
}

Explosion::~Explosion()
{

}

void Explosion::Update(double dt)
{
	bufferTime += dt;
	scaling += 2 * dt;
	if (bufferTime > 2)
	{
		done = true;
	}
}

bool Explosion::getDone()
{
	return done;
}

Vector3 Explosion::getPos()
{
	return Position;
}

float Explosion::getScale()
{
	return scaling;
}