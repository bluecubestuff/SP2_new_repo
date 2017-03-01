#ifndef _HULL_H
#define _HULL_H

#include "Module.h"

class Hull : public Module
{
public:
	Hull();
	Hull(int, float, string, string, string);
	~Hull();

	int getHullPoint();
	int getMass();
	void setHP(int);

	static int count;
private:
	int hullPoint;
	float mass;
};

#endif