#ifndef _BULLET_H
#define _BULLET_H

#include "Projectile.h"
#include "Mtx44.h"

class Bullet : public Projectile
{
public:
	Bullet();
	Bullet(Vector3, Vector3, Vector3, Vector3);
	~Bullet();

	bool outOfRange;
	Vector3 distance;

	void Update(double);

	Mtx44 getMatrix();
private:
	Mtx44 Stamp;
};

#endif