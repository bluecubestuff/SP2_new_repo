#include "NPC.h"

NPC::NPC(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	type = StudioProject::GEO_NPC;
	aabb->setAABB_Static_Objects(pos, size, size, size);
}
NPC::NPC(PlanetScene* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	type = PlanetScene::GEO_NPC;
	aabb->setAABB_Static_Objects(pos, size, size, size);
}
void NPC::interact()
{
	bool collide = true;

	if (collide == true)//aabb->AABBTOAABB == true
	{
		myscene->RenderTextOnScreen(myscene->meshList[StudioProject::GEO_TEXT], "NPC TEXT TEST", Color(0, 1, 0), 2, 8, 30);
	}
}