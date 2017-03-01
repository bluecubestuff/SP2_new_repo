#ifndef _NPC_H
#define _NPC_H

#include "StudioProject.h"
#include "PlanetScene.h"
#include "Vector3.h"
#include "ObjectRender.h"
#include "Application.h"
#include "Func_AABB.h"

#include <string>
using std::string;

class NPC
{
public:
	NPC();
	~NPC();

	void sell();
	void craft();
private:
	static int hPrice;
	static int sPrice;
	static int tPrice;
	
};
#endif