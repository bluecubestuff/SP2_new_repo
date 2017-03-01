#ifndef _LAND_PLAYER_H
#define _LAND_PLAYER_H

#include "landEntity.h"
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

	void Update(double dt);
	LandFPSCamera* getCam();
private:
	LandFPSCamera* FPS_CAM;
	Mtx44 Stamp;
};

#endif