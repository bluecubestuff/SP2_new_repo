#ifndef _BUILDING_H
#define _BUILDING_H

#include "Func_AABB.h"

#include <vector>
#include <map>

using std::vector;
using std::map;

class Building
{
public:

	Building();
	~Building();

	void set_building_AABB(Vector3,float);

private:

	map<unsigned, Building*> building_storage;
	vector<Func_AABB*> building_AABB;
	unsigned buildingID;

	Vector3 pos;
	float size;
};


#endif