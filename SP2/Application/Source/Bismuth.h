#ifndef _BISMUTH_H
#define _BISMUTH_H

#include "StudioProject.h"
#include "Vector3.h"
#include "ObjectRender.h"
#include "Application.h"
#include "Func_AABB.h"
#include "ship.h"

#include <string>
using std::string;

class Bismuth : public ObjectRender
{
public:
	Bismuth(StudioProject* scene, Vector3 pos, float size);
	~Bismuth(){};

	AABB* Bismuth_box;
	virtual void interact();
private:
	Func_AABB *aabb;
	Ship *ship;
	StudioProject *myscene;
};
#endif