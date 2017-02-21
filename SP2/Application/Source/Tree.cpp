#include "Tree.h"

Tree::Tree(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	aabb = new Func_AABB;
	
	type = StudioProject::GEO_TREE;
	aabb->setAABB_Static_Objects(pos, size);

	Tree_box = aabb->getAABB();
}
void Tree::interact()
{

}
AABB Tree::get_obj_AABB()
{
	return Tree_box;
}