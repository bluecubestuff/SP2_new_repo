#include "GalaxyGenerate.h"
#include "GalaxyScene.h"
#include "Sun.h"

GalaxyGenerate::GalaxyGenerate(GalaxyScene* scene) : myscene(scene), objfactory(scene)
{
}

GalaxyGenerate::~GalaxyGenerate()
{

}

void GalaxyGenerate::galaxyInIt()
{
	int x_axis, y_axis;
	Vector3 tempPos;
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			x_axis = Math::RandIntMinMax(-5500, 6000);
			y_axis = Math::RandIntMinMax(-3000, 2500);
			tempPos.Set(x_axis, y_axis, 1000);
			objfactory.createObject(new Sun(myscene, tempPos, 1, 1, 1.f, 1.f));
		}
	}

}

void GalaxyGenerate::build_galaxy()
{
	objfactory.renderObjects(3);
}

void GalaxyGenerate::galaxyUpdate()
{

}

map<unsigned, SolarGenerate*> GalaxyGenerate::system_database_getter()
{
	return system_database;
}