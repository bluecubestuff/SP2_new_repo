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

	void galaxyInIt();
	void galaxyUpdate();
	map<unsigned, SolarGenerate*> system_database_getter();

private:

	GalaxyGenerate();

	static GalaxyGenerate* instance;
	SolarGenerate* galaxy_map[10][10];
	map<unsigned, SolarGenerate*> system_database;
};

#endif