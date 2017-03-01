#ifndef _PLAYER_BULLET_H
#define _PLAYER_BULLET_H

#include "Projectile.h"
#include "Mtx44.h"

class playerBullet : public Projectile
{
public:
	playerBullet();
	playerBullet(Vector3, Vector3, Vector3, Vector3);
	~playerBullet();

	bool outOfRange;
	Vector3 distance;

	void Update(double);

	Mtx44 getMatrix();
private:
	Mtx44 Stamp;
};

#endif