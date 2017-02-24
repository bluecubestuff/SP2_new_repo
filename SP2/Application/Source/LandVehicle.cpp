#include "LandVehicle.h"

LandVehicle::LandVehicle()
{
	this->Position = Vector3(1000, 1, 1000);
	this->Forward = Vector3(0, 0, 1);
	this->Right = Vector3(1, 0, 0);
	this->Up = Vector3(0, 1, 0);
	Camera = new Camera3;
	hitbox = new Func_AABB;
	interactionBox = new Func_AABB;
	inVehicle = false;
	hitbox->updateAABB(1, 10, 1, this->Position);
	interactionBox->updateAABB(3, 10, 3, this->Position);
	this->Stamp = Mtx44(Right.x, Right.y, Right.z, 0, Up.x, Up.y, Up.z, 0, Forward.x, Forward.y, Forward.z, 0, Position.x, Position.y, Position.z, 1);
}

LandVehicle::~LandVehicle()
{
	delete Camera;
}

void LandVehicle::Update(double dt)
{
	Camera->Update(dt, false, this->Forward, this->Right, this->Up, this->Position);
	hitbox->updateAABB(1, 1, 1, this->Position);
	interactionBox->updateAABB(3, 3, 3, this->Position);

	if (Application::IsKeyPressed('W'))
	{
		this->Position += this->Forward * dt * 10.f;
	}

	this->Stamp = Mtx44(Right.x, Right.y, Right.z, 0, Up.x, Up.y, Up.z, 0, Forward.x, Forward.y, Forward.z, 0, Position.x, Position.y, Position.z, 1);
}

bool LandVehicle::getInVehicle()
{
	return inVehicle;
}

void LandVehicle::setInVehicle(bool set)
{
	this->inVehicle = set;
}