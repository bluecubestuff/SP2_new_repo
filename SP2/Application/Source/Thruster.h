#ifndef _THRUSTER_H
#define _THRUSTER_H

#include "Module.h"

class Thruster : public Module
{
public:
	Thruster();
	Thruster(int, float, string, string, string);
	~Thruster();

	int getThrust();
	float getPowerDraw();

	static int count;
private:
	int thrust;
	float powerDraw;
};

#endif