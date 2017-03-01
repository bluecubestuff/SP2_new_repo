#include "Camera3.h"
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
Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	this->up = defaultUp = up;
}

void Camera3::Update(double dt, bool notFixed, Vector3 f, Vector3 r, Vector3 u, Vector3 p)
{
	static const float CAMERA_SPEED = 40.f;
	if (!notFixed)
	{
		this->position = p - f * 10 + u * 3;
		this->target = p + f * 5;
		this->up = u;
	}
	else if (notFixed)
	{
		this->target = p;
	}
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

