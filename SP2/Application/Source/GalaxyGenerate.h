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
	GalaxyGenerate(GalaxyScene*);
	~GalaxyGenerate();
	
	void galaxyInIt();
	void build_galaxy();
	void galaxyUpdate();
	map<unsigned, SolarGenerate*> system_database_getter();

private:



	ObjectFactory objfactory;
	GalaxyScene* myscene;

	SolarGenerate* galaxy_map[7][7];
	map<unsigned, SolarGenerate*> system_database;
};

#endif







