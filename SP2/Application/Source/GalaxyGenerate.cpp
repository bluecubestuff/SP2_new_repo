#include "GalaxyGenerate.h"

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
		instance = new GalaxyGenerate;
	}
	return instance;
}

void GalaxyGenerate::galaxyInIt()
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			//galaxy_map[y][x] = new SolarGenerate()
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