#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>

using std::vector;
using std::string;

class StudioProject;

class Inventory
{
	friend class Iron;
	friend class Titanium;
	friend class Mithril;
	friend class Bismuth;
public:
	Inventory();
	~Inventory();

	void AddingStuff();
	vector <string> inventory;
private:
	float _Iron = 10.0;
	float _Titanium = 10.0;
	float _Mithril = 10.0;
	float _Bismuth = 10.0;
	StudioProject *myscene;
};

#endif