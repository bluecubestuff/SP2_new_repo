#ifndef _CUBE_H
#define _CUBE_H

#include "Vector3.h"

class Cube
{
public:
	Cube(Vector3 pos, float size) : cpos(pos), csize(size) {}
	~Cube() {}


private:

	Vector3 cpos;
	float csize;
};



#endif