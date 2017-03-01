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

	static GalaxyGenerate* get_instance();

	void galaxy_save_selection(int);
	void galaxyUpdate();

	int galaxy_id_getter();

	map<unsigned, SolarGenerate*> system_database; //system database
	
	void set_planet_id(int);
	int planet_id_getter();

private:

	GalaxyGenerate();
	static GalaxyGenerate* instance;		
	int galaxy_id;							//individual solarsystem in the galaxy ID
	int planet_id;							//individual planet in solar system's ID

	//ObjectFactory objfactory;
	//GalaxyScene* myscene;
	//SolarGenerate* galaxy_map[7][7];

};

#endif







