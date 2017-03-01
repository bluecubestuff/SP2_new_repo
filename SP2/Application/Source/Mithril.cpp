#include "Mithril.h"

Mithril::Mithril(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	aabb = new Func_AABB;
	type = StudioProject::GEO_MITHRIL;
	aabb->setAABB_Static_Objects(pos, size, size, size);
	Mithril_box = aabb->getAABB();
}
Mithril::Mithril(PlanetScene* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	aabb = new Func_AABB;
	type = PlanetScene::GEO_MITHRIL;
	aabb->setAABB_Static_Objects(pos, size, size, size);
	Mithril_box = aabb->getAABB();
}
void Mithril::interact()
{

}

AABB Mithril::get_obj_AABB()
{
	return Mithril_box;
}