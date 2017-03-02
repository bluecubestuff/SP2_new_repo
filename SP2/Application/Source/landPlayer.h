#ifndef _LAND_PLAYER_H
#define _LAND_PLAYER_H

#include "landEntity.h"
#include "Weapon.h"
#include "playerBullet.h"
#include "LandFPSCamera.h"
#include "Mtx44.h"

#include <vector>

using std::vector;

class LandEnemy;

class LandPlayer : public LandEntity
{
public:
	LandPlayer();		//for first time set up
	LandPlayer(Vector3, Vector3, Vector3, float);	//to load game
	~LandPlayer();

	void Combat(double dt, vector<LandEnemy*> meleeEnemies, vector<LandEnemy*> rangedEnemies);
	void Update(double dt);
	void Update(double dt, vector<LandEnemy*> meleeEnemies, vector<LandEnemy*> rangedEnemies);
	float calculateDistance(Vector3 playerPos, Vector3 enemyPos);
	LandFPSCamera* getCam();
	vector<playerBullet*> bullets;
	vector<LandEnemy*>::iterator it;
	bool meleeWeaponEquipped;
	bool rangedWeaponEquipped;
private:
	LandFPSCamera* FPS_CAM;
	Mtx44 Stamp;
};

#endif