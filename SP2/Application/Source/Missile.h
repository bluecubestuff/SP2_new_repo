#ifndef _MISSLE_H
#define _MISSLE_H

#include "Projectile.h"
#include "enemyShip.h"
#include "playerShip.h"

class Missile : public Projectile
{
public:
	Missile();
	Missile(EnemyShip* e, PlayerShip* me, float s, bool fire);
	~Missile();

	EnemyShip* e;
	PlayerShip* me;

	bool fire;

	Mtx44 Stamp;

	void tracking(double dt, Vector3 p);
	void checkTargets(vector<EnemyShip*> hostiles);
	void checkTargets(PlayerShip player);
};

#endif