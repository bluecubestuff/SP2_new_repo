#ifndef _TITANIUM_H
#define _TITANIUM_H

#include "StudioProject.h"
#include "Vector3.h"
#include "ObjectRender.h"
#include "Application.h"
#include "Func_AABB.h"
#include "ship.h"

#include <string>
using std::string;

class Titanium : public ObjectRender
{
public:
	Titanium(StudioProject* scene, Vector3 pos, float size);
	~Titanium(){};

	AABB* Titanium_box;
	virtual void interact();

private:
	Func_AABB *aabb;
	Ship *ship;
	StudioProject *myscene;
};
#endif