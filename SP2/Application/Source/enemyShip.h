#ifndef _ENEMY_SHIP_H
#define _ENEMY_SHIP_H

#include "ship.h"
#include "Func_AABB.h"
#include "DetectMemoryLeak.h"

//class for enemy ship generation and their behavior
class EnemyShip : public Ship
{
public:
	enum AI
	{
		PASSIVE,
		AGRESSIVE,
	};

	enum Passive_t
	{
		PIDLE,
		PCHASE,
		PATTACK,
		PBREAKOFF,
	};

	enum Agressive_t
	{
		AIDLE,
		ACHASE,
		AATTACK,
		ABREAKOFF,
	};

	EnemyShip();
	EnemyShip(Vector3 f, Vector3 u, Vector3 r, Vector3 p, float s, float size, float speed);
	~EnemyShip();
	void Update(double dt, Vector3 playerPos, Vector3 playerFor);
	bool getWithinSights();
	void setIGotYouInMySights(bool);
	bool getTargeted();
	void setTargeted(bool);
	float getSpeed();

	//chase
	void chase(double, Vector3);
	void idle(double);
	void breakoff(double, Vector3);

	bool agro;
	bool attack;
	bool deaded;
private:
	float turnSpeed;
	float speed;
	bool iGotYouInMySights;
	bool targeted;
	
	AI AI;
	Passive_t Passive;
	Agressive_t Agressive;
};

#endif