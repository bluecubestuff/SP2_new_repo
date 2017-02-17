#ifndef _FUNC_AABB_H
#define _FUNC_AABB_H

#include "AABB.h"
#include <vector>

class Func_AABB
{
public:

	Func_AABB();
	~Func_AABB();

	bool pointInAABB(const AABB&, const Vector3&);
	bool AABBtoAABB(const AABB&, const AABB&);
	void setAABB_Static_Objects(Vector3, float);
	void updateAABB(float sizeX, float sizeY, float sizeZ, Vector3 position);
	AABB getAABB();

private:

	std::vector<AABB> AABB_Storage;
	AABB TAABB;
};


#endif