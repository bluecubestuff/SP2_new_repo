#ifndef _IRON_H
#define _IRON_H

#include "StudioProject.h"
#include "PlanetScene.h"
#include "Vector3.h"
#include "ObjectRender.h"
#include "Application.h"
#include "Func_AABB.h"
#include "ship.h"

#include <string>
using std::string;

class Iron : public ObjectRender
{
public:
	Iron(StudioProject* scene, Vector3 pos, float size);
	Iron(PlanetScene* scene, Vector3 pos, float size);
	~Iron(){};

	AABB Iron_box;
	virtual void interact();
	virtual AABB get_obj_AABB();

private:
	Func_AABB *aabb;
	//Ship *ship;
	//StudioProject *myscene;
	PlanetScene* myscene;
};
#endif