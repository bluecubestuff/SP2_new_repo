#ifndef _SHIELD_H
#define _SHIELD_H

#include "Module.h"

class Shield : public Module
{
public:
	Shield();
	Shield(int, float, string, string, string);
	~Shield();

	int getShieldPoint();
	float getPowerDraw();
	void setSP(int);

	static int count;
private:
	int shieldPoint;
	float powerDraw;
};

#endif