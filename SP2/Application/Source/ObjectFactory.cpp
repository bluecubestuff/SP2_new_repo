#include "ObjectFactory.h"

ObjectFactory::ObjectFactory(StudioProject* scene)
{
	myscene = scene;
}

ObjectFactory::ObjectFactory(PlanetScene* scene)
{
	this->planet_scene = scene;
}

ObjectFactory::ObjectFactory(SystemScene* scene)
{
	this->system_scene = scene;
}

ObjectFactory::ObjectFactory(GalaxyScene* scene)
{
	this->galaxy_scene = scene;
}

void ObjectFactory::createObject(ObjectRender* obj)
{
	this->objContainer.push_back(obj);
}

void ObjectFactory::createSystemObject(ObjectRender* obj)
{	//for system only
	this->objContainer.push_back(obj);
}

void ObjectFactory::interactObjects()
{
	for (auto &a : objContainer)
	{
		a->interact();
	}
}

void ObjectFactory::renderObjects(unsigned id)
{
	if (id == 1)
	{	//SPACE SCENE (Studioproject scene)
		for (auto &a : objContainer)
		{
			a->render();
		}
	}
	else if (id == 2)
	{	//LAND SCENE (Planet scene)
		for (auto &a : objContainer)
		{
			a->render_planet();
		}
	}
	else if (id == 3)
	{	//GALAXY SCENE
		for (auto &a : objContainer)
		{
			a->render_galaxy();
		}
	}
}

void ObjectFactory::renderSystemObjects(float aRotate, float pRotate) //pass the rotation update
{
	for (auto &a : objContainer)
	{
		a->render_system_planets(aRotate, pRotate);
	}
	
}

void ObjectFactory::clearObjects()
{
	objContainer.clear();
}