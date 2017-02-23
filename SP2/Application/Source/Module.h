#ifndef _MODULE_H
#define _MODULE_H

#include <string>

#include "MyMath.h"
#include "Randomise.h"

using std::string;

class Module
{
public:
	string getId() { return this->ID; }
	string getType() { return this->type; }
	string getName() { return this->name; }
	Randomise hue;
protected:
	string ID;
	string type;
	string name;
};

#endif