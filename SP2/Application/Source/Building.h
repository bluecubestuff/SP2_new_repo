#ifndef _BUILDING_H
#define _BUILDING_H

#include "StudioProject.h"
#include "Vector3.h"
#include "ObjectRender.h"
#include "Application.h"
#include "Func_AABB.h"

#include <string>
using std::string;

class Building : public ObjectRender
{
public:
	Building(StudioProject* scene, Vector3 pos, float size);
	~Building(){};

	virtual void interact();

private:
	//vector<Func_AABB>;
	Func_AABB *aabb;
};
#endif