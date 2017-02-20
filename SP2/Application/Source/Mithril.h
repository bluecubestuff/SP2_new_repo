#ifndef _MITHRIL_H
#define _MITHRIL_H

#include "StudioProject.h"
#include "Vector3.h"
#include "ObjectRender.h"
#include "Application.h"
#include "Func_AABB.h"

#include <string>
using std::string;

class Mithril : public ObjectRender
{
public:
	Mithril(StudioProject* scene, Vector3 pos, float size);
	~Mithril(){};

	AABB* Mithril_box;

	virtual void interact();

private:
	Func_AABB *aabb;
};
#endif