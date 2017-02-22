#ifndef _POWER_PLANT_H
#define _POWER_PLANT_H

#include "Module.h"

class PowerPlant : public Module
{
public:
	PowerPlant();
	PowerPlant(float, string, string, string);
	~PowerPlant();

	float power;

	static int count;

	float getPower();
private:
	
};

#endif