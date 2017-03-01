#ifndef _LAND_PLAYER_H
#define _LAND_PLAYER_H

#include "landEntity.h"
#include "landEnemy.h"
#include "Weapon.h"
#include "LandFPSCamera.h"
#include "Mtx44.h"

#include <vector>

class LandPlayer : public LandEntity
{
public:
	LandPlayer();		//for first time set up
	LandPlayer(Vector3, Vector3, Vector3, float);	//to load game
	~LandPlayer();

	void Combat(double dt, Vector3 enemyPos, vector<LandEnemy*> landEnemies);
	void Update(double dt, Vector3 enemyPos, vector<LandEnemy*> landEnemies);
	float calculateDistance(Vector3 playerPos, Vector3 enemyPos);
	LandFPSCamera* getCam();
	vector<LandEnemy*>::iterator it;
private:
	bool meleeWeaponEquipped;
	bool rangedWeaponEquipped;
	LandFPSCamera* FPS_CAM;
	Mtx44 Stamp;
};

#endif