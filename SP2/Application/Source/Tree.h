#ifndef _TREE_H
#define _TREE_H

#include "StudioProject.h"
#include "PlanetScene.h"
#include "Vector3.h"
#include "ObjectRender.h"
#include "Application.h"

#include <string>
using std::string;

class Tree : public ObjectRender
{
public:
	Tree(StudioProject* scene, Vector3 pos, float size);
	Tree(PlanetScene* scene, Vector3 pos, float size);
	~Tree(){};

	AABB Tree_box;

	virtual void interact();
	virtual AABB get_obj_AABB();

private:
	Func_AABB *aabb;
};
#endif