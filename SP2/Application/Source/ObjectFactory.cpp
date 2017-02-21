#include "ObjectFactory.h"

ObjectFactory::ObjectFactory(StudioProject* scene)
{
	myscene = scene;
}

ObjectFactory::ObjectFactory(PlanetScene* scene)
{
	planet_scene = scene;
}

void ObjectFactory::createObject(ObjectRender* obj)
{
	objContainer.push_back(obj);
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

void ObjectFactory::clearObjects()
{
	objContainer.clear();
}