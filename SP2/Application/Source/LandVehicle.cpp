#include "LandVehicle.h"

float sizeCar = 10.f;

LandVehicle::LandVehicle()
{
	this->Position = Vector3(1000, 10, 900);
	this->Forward = Vector3(0, 0, 1);
	this->Right = Vector3(1, 0, 0);
	this->Up = Vector3(0, 1, 0);
	Camera = new Camera3;
	hitbox = new Func_AABB;
	interactionBox = new Func_AABB;
	inVehicle = false;
	hitbox->updateAABB(22, 20, 22, this->Position);
	interactionBox->updateAABB(25, 20, 25, this->Position);
	this->Stamp = Mtx44(sizeCar* Right.x, sizeCar* Right.y, sizeCar* Right.z, 0, sizeCar* Up.x, sizeCar* Up.y, sizeCar* Up.z, 0, sizeCar* Forward.x, sizeCar* Forward.y, sizeCar* Forward.z, 0, Position.x, Position.y, Position.z, 1);
}

LandVehicle::~LandVehicle()
{
	delete Camera;
}

void LandVehicle::Update(double dt)
{
	Camera->Update(dt, false, this->Forward, this->Right, this->Up, this->Position);
	hitbox->updateAABB(20, 20, 20, this->Position);
	interactionBox->updateAABB(25, 20, 25, this->Position);

	if (Application::IsKeyPressed('W'))
	{
		this->Position += this->Forward * dt * 50.f;
	}
	else if (Application::IsKeyPressed('S'))
	{
		this->Position += this->Forward * dt * -40.f;
	}

	if (Application::IsKeyPressed('A'))
	{
		Mtx44 rotation;
		rotation.SetToRotation(20.f * dt, 0, 1, 0);
		this->Forward = rotation * this->Forward;
	}
	else if (Application::IsKeyPressed('D'))
	{
		Mtx44 rotation;
		rotation.SetToRotation(-20.f * dt, 0, 1, 0);
		this->Forward = rotation * this->Forward;
	}
	this->Right = (Vector3(0, 1, 0).Cross(this->Forward)).Normalized();

	this->Stamp = Mtx44(sizeCar* Right.x, sizeCar* Right.y, sizeCar* Right.z, 0, sizeCar* Up.x, sizeCar* Up.y, sizeCar* Up.z, 0, sizeCar* Forward.x, sizeCar* Forward.y, sizeCar* Forward.z, 0, Position.x, Position.y, Position.z, 1);
}

bool LandVehicle::getInVehicle()
{
	return inVehicle;
}

void LandVehicle::setInVehicle(bool set)
{
	this->inVehicle = set;
}