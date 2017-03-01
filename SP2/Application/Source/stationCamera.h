#ifndef _STATION_CAMERA_H
#define _STATION_CAMERA_H

#include <vector>

#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"
#include "MouseControl.h"
#include "Func_AABB.h"
#include "NPC.h"

using std::vector;

class StationCamera : public Camera
{
public:
	StationCamera();
	~StationCamera();

	bool craft;
	bool sell;

	void Init(Vector3, Vector3, Vector3);
	void Update(double dt);
private:
	float pitchLimit;

	Vector3 right;

	POINT mousePos;

	Mouse mouse;

	Func_AABB* Area;
	Func_AABB* hitbox;	//#hardcodeisbestcode

	NPC npc;

	vector<Func_AABB*> hitboxes;
};

#endif