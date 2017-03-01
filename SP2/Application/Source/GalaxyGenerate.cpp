#include "GalaxyGenerate.h"
#include "GalaxyScene.h"

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

void GalaxyGenerate::galaxy_save_selection(int id)
{
	this->galaxy_id = id;
}

void GalaxyGenerate::galaxyUpdate()
{

}

int GalaxyGenerate::galaxy_id_getter()
{
	return this->galaxy_id;
}

void GalaxyGenerate::set_planet_id(int temp_id)
{
	planet_id = temp_id;
}

int GalaxyGenerate::planet_id_getter()
{
	return planet_id;
}