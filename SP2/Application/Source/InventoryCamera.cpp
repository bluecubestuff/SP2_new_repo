#include "InventoryCamera.h"
#include "Application.h"
#include "Mtx44.h"
#include "MatrixStack.h"
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//debugging purposes
#include <iostream>
using std::cout;
using std::endl;

//extern GLFWwindow* m_window;
InventoryCamera::InventoryCamera()
{
}

InventoryCamera::~InventoryCamera()
{
}

void InventoryCamera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	this->up = defaultUp = up;
}

void InventoryCamera::Update(double dt, bool notFixed, Vector3 f, Vector3 r, Vector3 u, Vector3 p)
{
	static const float CAMERA_SPEED = 40.f;
	if (!notFixed)
	{
		this->position = p - f * 10 + u * 5;
		this->target = p;
		this->up = u;
	}
	else if (notFixed)
	{
		this->target = p;
	}
}

void InventoryCamera::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

