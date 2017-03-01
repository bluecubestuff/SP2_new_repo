#ifndef _ENEMY_BULLET_H
#define _ENEMY_BULLET_H

#include "Projectile.h"
#include "Mtx44.h"

class enemyBullet : public Projectile
{
public:
	enemyBullet();
	enemyBullet(Vector3, Vector3, Vector3, Vector3);
	~enemyBullet();

	bool outOfRange;
	Vector3 distance;

	void Update(double);

	Mtx44 getMatrix();
private:
	Mtx44 Stamp;
};

#endif