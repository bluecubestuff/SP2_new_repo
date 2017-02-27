#include "GalaxyGenerate.h"
#include "GalaxyScene.h"
#include "Sun.h"

GalaxyGenerate::GalaxyGenerate()
{
}

GalaxyGenerate::~GalaxyGenerate()
{

}

GalaxyGenerate* GalaxyGenerate::get_instance()
{
	if (!instance)
	{
		instance = new GalaxyGenerate();
	}
	return instance;
}

void GalaxyGenerate::galaxyInIt(GalaxyScene* scene)
{
	objfactory = new ObjectFactory(scene);
	int x_axis, y_axis;
	Vector3 tempPos;
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			x_axis = Math::RandIntMinMax(-5500, 6000);
			y_axis = Math::RandIntMinMax(-3000, 2500);
			tempPos.Set(x_axis, y_axis, 1000);
			objfactory->createObject(new Sun(scene, tempPos, 1, 1, 1.f, 1.f));
		}
	}

}

void GalaxyGenerate::galaxyUpdate()
{

}

map<unsigned, SolarGenerate*> GalaxyGenerate::system_database_getter()
{
	return system_database;
}