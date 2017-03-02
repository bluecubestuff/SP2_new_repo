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
	myscene = scene;
	aabb = new Func_AABB;
	type = PlanetScene::GEO_MITHRIL;
	aabb->setAABB_Static_Objects(pos, size + 2, size + 5, size + 2);
	Mithril_box = aabb->getAABB();
	isMined = false;
}
void Mithril::interact()
{
	myscene->RenderTextOnScreen(myscene->meshList[PlanetScene::GEO_TEXT], "Mine Mithril [E]", Color(0, 1, 0), 2, 1, 4);
	if (Application::IsKeyPressed('E') && !isMined)
	{
		Currency::get_instance()->add_mineral("mithril");
		type = PlanetScene::GEO_ROCK;
		isMined = true;
	}
	//float x = ((ship->getter("position")).x - position.x);
	//float y = ((ship->getter("position")).y - position.y);
	//float z = 5.0f;

	//if ( x < 10.0 && y < 10.0 && Application::IsKeyPressed('Z'))
	//{
	//	scale -= (z * myscene->_dt);
	//	if (scale < 1)
	//	{
	//		position.y += -500;
	//		myscene->MithrilValue += 1;
	//	}
	//}
}

AABB Mithril::get_obj_AABB()
{
	return Mithril_box;
}
