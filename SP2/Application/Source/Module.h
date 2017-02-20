#ifndef _MODULE_H
#define _MODULE_H

#include <string>

#include "Randomise.h"

using std::string;

class Module
{
public:
	string getId() { return this->ID; }
	string getType() { return this->type; }
	string getName() { return this->name; }
protected:
	string ID;
	string type;
	string name;
};

#endif