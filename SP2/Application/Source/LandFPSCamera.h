#ifndef _LAND_FPS_CAMERA_H
#define _LAND_FPS_CAMERA_H

#include "Camera.h"
#include "MouseControl.h"
#include "Mtx44.h"

#include <windows.h>

class LandFPSCamera : public Camera
{
public:
	LandFPSCamera();
	~LandFPSCamera();

	Mouse* mouse;

	void Init(Vector3, Vector3, Vector3);
	void Update(double, Vector3 &, Vector3&);
private:
	Vector3 right;
	Vector3 Inertia;

	POINT currMousePos;

	bool jump;
};

#endif