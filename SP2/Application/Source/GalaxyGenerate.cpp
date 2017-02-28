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