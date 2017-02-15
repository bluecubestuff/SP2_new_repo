#ifndef _ENEMY_SHIP_H
#define _ENEMY_SHIP_H

#include "ship.h"
#include "DetectMemoryLeak.h"

class EnemyShip : public Ship
{
public:
	EnemyShip();
	EnemyShip(Vector3 f, Vector3 u, Vector3 r, Vector3 p, float s);
	~EnemyShip();
	void Update(double dt, Vector3 playerPos, Vector3 playerFor);
private:
	float turnSpeed;
};

#endif