#ifndef _ROCK_H
#define _ROCK_H

#include "StudioProject.h"
#include "PlanetScene.h"
#include "Vector3.h"
#include "ObjectRender.h"
#include "Application.h"

#include <string>
using std::string;

class Rock : public ObjectRender
{
public:
	Rock(StudioProject* scene, Vector3 pos, float size);
	Rock(PlanetScene* scene, Vector3 pos, float size);
	~Rock(){};

	AABB Rock_box;

	virtual void interact();
	virtual AABB get_obj_AABB();

private:
	Func_AABB *aabb;
};

#endif
