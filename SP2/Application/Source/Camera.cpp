#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"
#include "MouseControl.h"

Camera::Camera()
{
	Reset();
}

Camera::~Camera()
{
}

void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
	forward = target - position;
	forward.Normalize();
}

void Camera::Reset()
{
	position.Set(1, 0, 0);
	target.Set(0, 0, 0);
	up.Set(0, 1, 0);
}

void Camera::Update(double dt)
{
	static float CAMERA_SPEED = 20.f;
	Vector3 view = target - position;
	Vector3 right = view.Cross(this->up);
	view.Normalize();
	right.Normalize();
	/*if(Application::IsKeyPressed('E'))
	{
		position += right * CAMERA_SPEED * dt;
	}
	else if(Application::IsKeyPressed('Q'))
	{
		position -= right * CAMERA_SPEED * dt;
	}
	if(Application::IsKeyPressed('W'))
	{
		position += view * CAMERA_SPEED * dt;
	}
	else if(Application::IsKeyPressed('S'))
	{
		position -= view * CAMERA_SPEED * dt;
	}
	if (Application::IsKeyPressed('A'))
	{
		Mtx44 rotation;
		rotation.SetToRotation(-100.f * dt, forward.x, forward.y, forward.z);
		up = rotation * up;
	}
	else if (Application::IsKeyPressed('D'))
	{
		Mtx44 rotation;
		rotation.SetToRotation(100.f * dt, forward.x, forward.y, forward.z);
		up = rotation * up;
	}
	if (Application::IsKeyPressed('R'))
	{
		position += up * CAMERA_SPEED * dt;
	}
	else if (Application::IsKeyPressed('F'))
	{
		position -= up * CAMERA_SPEED * dt;
	}*/
	if (Application::IsKeyPressed(VK_SPACE))
	{
		CAMERA_SPEED = 1000.f;
	}
	else
	{
		CAMERA_SPEED = 20.f;
	}
	//==================================================================
	//if (Application::IsKeyPressed(VK_UP))
	//{
	//	Mtx44 rotation;
	//	rotation.SetToRotation(100.f * dt, right.x, 0, right.z);
	//	forward = rotation * forward;
	//	up = rotation * up;
	//}
	//else if (Application::IsKeyPressed(VK_DOWN))
	//{
	//	Mtx44 rotation;
	//	rotation.SetToRotation(-100.f * dt, right.x, 0, right.z);
	//	forward = rotation * forward;
	//	up = rotation * up;
	//}
	//if (Application::IsKeyPressed(VK_LEFT))
	//{
	//	Mtx44 rotation;
	//	rotation.SetToRotation(100.f * dt, up.x, up.y, up.z);
	//	forward = rotation * forward;
	//}
	//else if (Application::IsKeyPressed(VK_RIGHT))
	//{
	//	Mtx44 rotation;
	//	rotation.SetToRotation(-100.f * dt, up.x, up.y, up.z);
	//	forward = rotation * forward;
	//}
	//==================================================================
	target = forward + position;
}