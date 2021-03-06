#ifndef _FUNC_AABB_H
#define _FUNC_AABB_H

#include "AABB.h"
#include <vector>

class Func_AABB
{
public:

	Func_AABB(); 
	Func_AABB(Vector3, Vector3);
	~Func_AABB();

	bool pointInAABB(const Vector3&);
	bool AABBtoAABB(const AABB&);
	void setAABB_Static_Objects(Vector3, float, float, float);
	void updateAABB(float sizeX, float sizeY, float sizeZ, Vector3 position);
	AABB getAABB();
	bool pointInAABB(const Vector3&, const AABB&);
	bool mouseInAABB(Vector3);
private:

	std::vector<AABB> AABB_Storage;
	AABB TAABB;
};


#endif