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

LandFPSCamera* LandPlayer::getCam()
{
	return FPS_CAM;
}