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
	void setThrust(int);

	static int count;
private:
	int thrust;
	float powerDraw;
};

#endif