#ifndef _GREEN_PLANET_H
#define _GREEN_PLANET_H

#include "SystemScene.h"
#include "ObjectRender.h"

class GreenPlanet : public ObjectRender
{
public:
	GreenPlanet(SystemScene* scene, Vector3 pos, float sizeX, float sizeZ,float aRotate,float pRotate);
	~GreenPlanet();

	AABB green_planet_box;

	virtual void interact();
	virtual AABB get_obj_AABB();

private:
	Func_AABB* aabb;
};


#endif