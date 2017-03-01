#include "landPlayer.h"

LandPlayer::LandPlayer()
{
	FPS_CAM = new LandFPSCamera;
}

LandPlayer::LandPlayer(Vector3 pos, Vector3 f, Vector3 r, float health)
{
	FPS_CAM = new LandFPSCamera;
	this->Position = pos;
	this->Forward = f;
	this->Up = Vector3(0, 1, 0);
	this->Right = r;

	this->setHealth(health);
	FPS_CAM->Init(pos, f, this->Up);
	this->Stamp = Mtx44(Right.x, Right.y, Right.z, 0, Up.x, Up.y, Up.z, 0, Forward.x, Forward.y, Forward.z, 0, Position.x, Position.y, Position.z, 1);
}

LandPlayer::~LandPlayer()
{
	delete FPS_CAM;
}

void LandPlayer::Update(double dt)
{
	FPS_CAM->Update(dt, Position, Forward);
	this->Right = (Forward.Cross(Vector3(0, 1, 0))).Normalized();
	this->Stamp = Mtx44(Right.x, Right.y, Right.z, 0, Up.x, Up.y, Up.z, 0, Forward.x, Forward.y, Forward.z, 0, Position.x, Position.y, Position.z, 1);
}

void LandPlayer::Combat(double dt, Vector3 enemyPos, vector<LandEnemy*> landEnemies)
{
	if (Application::IsKeyPressed('Q'))
	{
		meleeWeaponEquipped = true;
		rangedWeaponEquipped = false;
	}
	if (Application::IsKeyPressed('E'))
	{
		rangedWeaponEquipped = true;
		meleeWeaponEquipped = false;
	}

	for (it = landEnemies.begin(); it != landEnemies.end(); it++)
	{
		if (meleeWeaponEquipped == true && calculateDistance(Position, enemyPos) < 30)
		{
			if (Application::IsKeyPressed(VK_LEFT))
			{
				(*it)->modifyHealth("decrease", 35);
			}
		}
	}
}

float LandPlayer::calculateDistance(Vector3 playerPos, Vector3 enemyPos)
{
	float dist;

	float x1 = playerPos.x;
	float x2 = enemyPos.x;

	float y1 = playerPos.z;
	float y2 = enemyPos.z;

	float x = x1 - x2;
	float y = y1 - y2;

	dist = pow(x, 2) + pow(y, 2);
	dist = sqrt(dist);

	return dist;
}

LandFPSCamera* LandPlayer::getCam()
{
	return FPS_CAM;
}