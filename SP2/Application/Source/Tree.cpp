#include "Tree.h"

Tree::Tree(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	type = StudioProject::GEO_TREE;
}
void Tree::interact()
{

}