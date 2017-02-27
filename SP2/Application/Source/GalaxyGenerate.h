#ifndef _GALAXY_GENERATE_H
#define _GALAXY_GENERATE_H

#include <vector>
#include <map>

using std::vector;
using std::map;

#include "SolarGenerate.h"

class GalaxyGenerate
{
public:

	~GalaxyGenerate();
	
	static GalaxyGenerate *get_instance();

	void galaxyInIt(GalaxyScene*);
	void galaxyUpdate();
	map<unsigned, SolarGenerate*> system_database_getter();

private:

	GalaxyGenerate();

	ObjectFactory* objfactory;
	GalaxyScene* myscene;

	static GalaxyGenerate* instance;
	SolarGenerate* galaxy_map[7][7];
	map<unsigned, SolarGenerate*> system_database;
};

#endif







