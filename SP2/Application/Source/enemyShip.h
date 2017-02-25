#ifndef _ENEMY_SHIP_H
#define _ENEMY_SHIP_H

#include "ship.h"
#include "Func_AABB.h"
#include "SpaceEnemy.h"
#include "DetectMemoryLeak.h"

//class for enemy ship generation and their behavior
class EnemyShip : public Ship
{
public:
	EnemyShip();
	EnemyShip(Vector3 f, Vector3 u, Vector3 r, Vector3 p, float s, float size, float speed);
	~EnemyShip();
	void Update(double dt, Vector3 playerPos, Vector3 playerFor);
	bool getWithinSights();
	void setIGotYouInMySights(bool);
	bool getTargeted();
	void setTargeted(bool);
	float getSpeed();

	bool deaded;
private:
	float turnSpeed;
	float speed;
	bool iGotYouInMySights;
	bool targeted;
};

#endif