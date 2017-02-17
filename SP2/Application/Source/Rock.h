#ifndef _ROCK_H
#define _ROCK_H

#include "StudioProject.h"
#include "Vector3.h"
#include "ObjectRender.h"


#include <string>
using std::string;

class Rock : public ObjectRender
{
public:
	Rock(StudioProject* scene, Vector3 pos, float size);
	~Rock(){};

	virtual void interact();
};

#endif
