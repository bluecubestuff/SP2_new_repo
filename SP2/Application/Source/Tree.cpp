#include "Tree.h"

Tree::Tree(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	type = StudioProject::GEO_TREE;
	aabb->setAABB_Static_Objects(pos, size);
}
void Tree::interact()
{

}