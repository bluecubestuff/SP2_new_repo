#ifndef ObjectFactory_H
#define ObjectFactory_H

#include <vector>
#include "ObjectRender.h"
//#include "LandGenerate.h"

class StudioProject;

class ObjectFactory
{

public:
	ObjectFactory(StudioProject* scene);
	~ObjectFactory() {};

	void createObject(ObjectRender* obj);
	void interactObjects();
	void renderObjects();

	std::vector<ObjectRender*> objContainer;

private:
	StudioProject* myscene;
	//LandGenerate* land;

};
#endif