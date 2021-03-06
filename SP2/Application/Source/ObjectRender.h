#ifndef _OBJECT_RENDER_H
#define _OBJECT_RENDER_H

#include "Vector3.h"
#include "Application.h"
#include "Func_AABB.h"

class StudioProject;
class PlanetScene;
class SystemScene;
class GalaxyScene;

class ObjectRender //TODO
{
public:
	ObjectRender(StudioProject* scene, Vector3 pos, float size);
	ObjectRender(PlanetScene* scene, Vector3 pos, float size);
	ObjectRender(SystemScene* scene, Vector3 pos, float sizeX, float sizeZ, float aRotate, float pRotate);
	ObjectRender(GalaxyScene* scene, Vector3 pos, float sizeX, float sizeZ, float aRotate, float pRotate);
	virtual ~ObjectRender(){};

	virtual void interact() = 0;

	void render();
	void render_planet();
	void render_system_planets(float,float);
	void render_galaxy();

	Vector3 position;
	float scale;
	float scaleX, scaleZ;
	float rotatespeed = 0;
	float aroundRotate, planetRotate;

	StudioProject* myscene;

	unsigned type;
	unsigned objID; //for the planets
	virtual AABB get_obj_AABB() = 0;

private:

	PlanetScene* planetscene;
	SystemScene* systemscene;
	GalaxyScene* galaxyscene;
};


#endif