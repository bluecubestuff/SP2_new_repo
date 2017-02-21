#ifndef _OBJECT_RENDER_H
#define _OBJECT_RENDER_H

#include "Vector3.h"
#include "Application.h"
#include "Func_AABB.h"

class StudioProject;
class PlanetScene;

class ObjectRender //TODO
{
public:
	ObjectRender(StudioProject* scene, Vector3 pos, float size);
	ObjectRender(PlanetScene* scene, Vector3 pos, float size);
	virtual ~ObjectRender(){};

	virtual void interact() = 0;

	void render();
	void render_planet();

	Vector3 position;
	float scale;
	float rotatespeed = 0;

	StudioProject* myscene;
	PlanetScene* planetScene;

	unsigned type;
	virtual AABB get_obj_AABB() = 0;

private:
};


#endif