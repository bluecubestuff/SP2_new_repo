#ifndef _INVENTORY_CAMERA_H
#define _INVENTORY_CAMERA_H

#include "Camera.h"
#include "DetectMemoryLeak.h"

#include <windows.h>

class InventoryCamera : public Camera
{
public:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	float limitPitch;
	float yawRight, yawLeft;

	float timeCheck;

	POINT mp; //mousePos for scene area
	POINT curMousePos;

	InventoryCamera();
	~InventoryCamera();

	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt, bool notFixed, Vector3 f, Vector3 r, Vector3 u, Vector3 p);
	virtual void Reset();

};

#endif