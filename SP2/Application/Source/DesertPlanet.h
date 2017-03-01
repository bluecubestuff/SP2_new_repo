#ifndef _DESERT_PLANET_H
#define _DESERT_PLANET_H

#include "SystemScene.h"
#include "ObjectRender.h"

class DesertPlanet : public ObjectRender
{
public:
	DesertPlanet(SystemScene* scene, Vector3 pos, float sizeX, float sizeY, float aRotate, float pRotate);
	~DesertPlanet();

	AABB green_planet_box;

	virtual void interact();
	virtual AABB get_obj_AABB();
	void set_aabb(float);

private:
	Func_AABB* aabb;
};


#endif