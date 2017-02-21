#ifndef ObjectFactory_H
#define ObjectFactory_H

#include <vector>
#include "ObjectRender.h"
#include "Func_AABB.h"
//#include "LandGenerate.h"

class StudioProject;

class ObjectFactory
{

public:
	ObjectFactory(StudioProject* scene);
	~ObjectFactory() { objContainer.clear(); };

	void createObject(ObjectRender* obj);
	void interactObjects();
	void renderObjects();
	void clearObjects();

	std::vector<ObjectRender*> objContainer;
	//std::vector<Func_AABB*> obj_AABB_Container;

private:
	StudioProject* myscene;
	//LandGenerate* land;

};
#endif