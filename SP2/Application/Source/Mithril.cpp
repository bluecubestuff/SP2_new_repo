#include "Mithril.h"

Mithril::Mithril(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	type = StudioProject::GEO_MITHRIL;
	//aabb->setAABB_Static_Objects(pos, size);
}
void Mithril::interact()
{

}