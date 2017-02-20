#ifndef _TREE_H
#define _TREE_H

#include "StudioProject.h"
#include "Vector3.h"
#include "ObjectRender.h"

#include <string>
using std::string;

class Tree : public ObjectRender
{
public:
	Tree(StudioProject* scene, Vector3 pos, float size);
	~Tree(){};

	virtual void interact();
};
#endif