#include "LandFPSCamera.h"

#include <iostream>

LandFPSCamera::LandFPSCamera()
{
	mouse = new Mouse;
}
LandFPSCamera::~LandFPSCamera()
{
	delete mouse;
}

void LandFPSCamera::Init(Vector3 pos, Vector3 target, Vector3 up)
{
	this->position = pos;
	this->target = position + target;
	this->up = up;

	this->forward = target;
	forward.Normalize();

	right = forward.Cross(Vector3(0, 1, 0));
	right.Normalize();

	currMousePos.x = 0;
	currMousePos.y = 0;

	this->jump = false;
	Inertia = Vector3(0, 0, 0);

	//for collsion
	pFront = position + forward;		
	pBack = position + (forward * -1);	
	pRight = position + (right);		
	pLeft = position + (right * -1);	

	cForward = false; 
	cBack = false;
	cRight = false;
	cLeft = false;
}

void LandFPSCamera::Update(double dt, Vector3& fuck, Vector3& fuckfuck)
{
	static const float CAMERA_SPEED = 0.01f * dt;
	static float MOVEMENT_SPEED = 0.3f * dt;
	static float pitchLimit = 0.f;

	pFront = position + forward;
	pBack = position + (forward * -1);
	pRight = position + (right);
	pLeft = position + (right * -1);

	currMousePos = mouse->mouseMovement();

	Vector3 temp = forward;
	temp.y = 0;
	temp.Normalize();


	fuck = position;
	fuckfuck = temp;

	Vector3 strafe = right;
	strafe.y = 0;
	strafe.Normalize();

	if (Application::IsKeyPressed('W'))
	{
		if (!cForward && pFront.x < 2500 && pFront.x > 0 && pFront.z < 2500 && pFront.z > 0)
		{
			Inertia = temp * MOVEMENT_SPEED;
			position += Inertia;
		}
	}
	else if (Application::IsKeyPressed('S'))
	{
		if (!cBack && pBack.x < 2500 && pBack.x > 0 && pBack.z < 2500 && pBack.z > 0)
		{
			Inertia = -temp * MOVEMENT_SPEED;
			position += Inertia;
		}
	}
	if (Application::IsKeyPressed('D'))
	{
		if (!cRight  && pRight.x < 2500 && pRight.x > 0 && pRight.z < 2500 && pRight.z > 0)
		{
			Inertia = strafe * MOVEMENT_SPEED * 0.5;
			position += Inertia;
		}
	}
	else if (Application::IsKeyPressed('A') && pLeft.x < 2500 && pLeft.x > 0 && pLeft.z < 2500 && pLeft.z > 0)
	{
		if (!cLeft)
		{
			Inertia = -strafe * MOVEMENT_SPEED * 0.5;
			position += Inertia;
		}
	}
	if (Application::IsKeyPressed(VK_SPACE) && !jump)
	{
		jump = true;
	}
	if (Application::IsKeyPressed(VK_LSHIFT))
	{
		MOVEMENT_SPEED = 0.5f;
	}
	else
	{
		MOVEMENT_SPEED = 0.3f;
	}

	if (jump)
	{
		static Vector3 a = Vector3(0, 1, 0);
		static Vector3 g = Vector3(0, -2.f, 0);
		a += g * dt;
		position += a;
		std::cout << a << std::endl;
		if (position.y <= 3)
		{
			a = Vector3(0, 1.f, 0);
			g = Vector3(0, -3.f, 0);
			position.y = 5;
			jump = false;
		}
	}
	
	if (currMousePos.x)
	{
		Mtx44 rotation;
		rotation.SetToRotation(CAMERA_SPEED * -currMousePos.x, 0, 1, 0);
		forward = rotation * forward;
		right = rotation * right;
	}
	if (currMousePos.y < 0 && pitchLimit > -80)
	{
		Mtx44 rotation;
		rotation.SetToRotation(-CAMERA_SPEED * currMousePos.y, right.x, right.y, right.z);
		forward = rotation * forward;
		//up = rotation * up;
		pitchLimit += CAMERA_SPEED * currMousePos.y;
	}
	else if (currMousePos.y > 0 && pitchLimit < 80)
	{
		Mtx44 rotation;
		rotation.SetToRotation(-CAMERA_SPEED * currMousePos.y, right.x, right.y, right.z);
		forward = rotation * forward;
		//up = rotation * up;
		pitchLimit += CAMERA_SPEED * currMousePos.y;
	}
	target = position + forward;

	up = (right.Cross(forward)).Normalized();

}