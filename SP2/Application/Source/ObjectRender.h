#ifndef _OBJECT_RENDER_H
#define _OBJECT_RENDER_H

#include "Vector3.h"

class StudioProject;

class ObjectRender //TODO
{
public:
	ObjectRender(StudioProject* scene, Vector3 pos, float size);
	virtual ~ObjectRender(){};

	virtual void interact() = 0;

	void render();

	Vector3 position;
	float scale;
	float rotatespeed = 0;

	StudioProject *myscene;
	unsigned type;

private:

};


#endif