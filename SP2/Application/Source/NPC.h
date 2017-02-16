#ifndef _NPC_H
#define _NPC_H

#include "StudioProject.h"
#include "Vector3.h"
#include "ObjectRender.h"
#include "Application.h"

#include <string>
using std::string;

class NPC : public ObjectRender
{
public:
	NPC(StudioProject* scene, Vector3 pos, float size);
	~NPC(){};

	virtual void interact();
};
#endif