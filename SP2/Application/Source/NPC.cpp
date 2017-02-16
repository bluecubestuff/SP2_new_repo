#include "NPC.h"

NPC::NPC(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	type = StudioProject::GEO_NPC;
	aabb->setAABB_Static_Objects(pos, size);
}
void NPC::interact()
{

}