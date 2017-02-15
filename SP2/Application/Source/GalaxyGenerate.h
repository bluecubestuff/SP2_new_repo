#ifndef _GALAXY_GENERATE_H
#define _GALAXY_GENERATE_H

#include <vector>
#include <map>

using std::vector;
using std::map;


class GalaxyGenerate
{
public:

	GalaxyGenerate();
	~GalaxyGenerate();

	void galaxyInIt();
	void galaxyUpdate();

protected:
typedef vector<vector<int>> doubleVector;
	doubleVector GalaxyArray;

};

#endif