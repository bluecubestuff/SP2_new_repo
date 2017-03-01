#ifndef _SUN_H
#define _SUN_H

#include "GalaxyScene.h"
#include "ObjectRender.h"

class Sun : public ObjectRender
{
public:

	Sun(GalaxyScene* scene, Vector3 pos, float sizeX, float sizeY, float aRotate, float pRotate);
	~Sun();

	AABB sun_box;
	 
	virtual void interact();
	virtual AABB get_obj_AABB();
	void set_aabb(float);

private:

	Func_AABB* aabb;
};


#endif