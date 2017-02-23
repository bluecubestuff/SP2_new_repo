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

void ObjectFactory::createObject(ObjectRender* obj)
{
	this->objContainer.push_back(obj);
}

void ObjectFactory::createSystemObject(ObjectRender* obj)
{
	this->systemObjContainer.push_back(obj);
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
	{
		for (auto &a : objContainer)
		{
			a->render();
		}
	}
	else if (id == 2)
	{
		for (auto &a : objContainer)
		{
			a->render_planet();
		}
	}
}

void ObjectFactory::renderSystemObjects(float aRotate, float pRotate) //pass the rotation update
{
	for (auto &a : systemObjContainer)
	{
		a->render_system_planets(aRotate, pRotate);
	}
	
}

void ObjectFactory::clearObjects()
{
	objContainer.clear();
}