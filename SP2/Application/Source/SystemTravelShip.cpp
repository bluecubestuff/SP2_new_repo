#include "SystemTravelShip.h"
#include "Mtx44.h"
#include "Application.h"

SystemTravelShip::SystemTravelShip()
{
	this->position = Vector3(0, 5000, 0);
	this->forward = Vector3(0, -1, 0);
	this->rotate = 0;
}

SystemTravelShip::~SystemTravelShip()
{

}

void SystemTravelShip::Update(double dt)
{
	if (Application::IsKeyPressed('W'))
	{
		position += forward * dt * 400;
	}
	else if (Application::IsKeyPressed('S'))
	{
		position -= forward * dt * 400;
	}

	if (Application::IsKeyPressed('A'))
	{
		rotate += 45.f * dt;
		Mtx44 rotation;
		rotation.SetToRotation(45.f * dt, 0, 0, 1);
		forward = rotation * forward;
	}
	else if (Application::IsKeyPressed('D'))
	{
		rotate -= 45.f * dt;
		Mtx44 rotation;
		rotation.SetToRotation(45.f * -dt, 0, 0, 1);
		forward = rotation * forward;
	}
}