#include "SystemTravelShip.h"
#include "Mtx44.h"
#include "Application.h"

SystemTravelShip::SystemTravelShip()
{
	this->position = Vector3(1000, 1000, 1000);
	this->forward = Vector3(0, -1, 0);
	this->rotate = 0;
	this->func_aabb = new Func_AABB;
}

SystemTravelShip::~SystemTravelShip()
{
	delete this->func_aabb;
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

	//Vector3 temp_pos;
	//temp_pos.Set(position.x + 1000, position.y - 4000, position.z + 1000);

	//std::cout << "posX playership: " << temp_pos.x << "\n";
	//std::cout << "posZ playership: " << temp_pos.y << "\n";

	func_aabb->updateAABB(100.f, 100.f, 100.f, position);
}

Func_AABB* SystemTravelShip::func_aabb_getter()
{
	return func_aabb;
}