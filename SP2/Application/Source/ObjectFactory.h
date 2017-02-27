#ifndef ObjectFactory_H
#define ObjectFactory_H

#include <vector>
#include "ObjectRender.h"
#include "Func_AABB.h"
//#include "LandGenerate.h"

class StudioProject;
class PlanetScene;
class SystemScene;
class GalaxyScene;

class ObjectFactory
{

public:
	ObjectFactory(StudioProject* scene);
	ObjectFactory(PlanetScene* scene);
	ObjectFactory(SystemScene* scene);
	ObjectFactory(GalaxyScene* scene);
	~ObjectFactory() 
	{ 
		objContainer.clear();
	};

	void createObject(ObjectRender* obj);
	void createSystemObject(ObjectRender* obj);
	void interactObjects();
	void renderObjects(unsigned);
	void renderSystemObjects(float, float);
	void clearObjects();

	std::vector<ObjectRender*> systemObjContainer;
	std::vector<ObjectRender*> objContainer;
	//std::vector<Func_AABB*> obj_AABB_Container;

private:

	StudioProject* myscene;
	PlanetScene* planet_scene;
	SystemScene* system_scene;
	GalaxyScene* galaxy_scene;
	//LandGenerate* land;

};
#endif