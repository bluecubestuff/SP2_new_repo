#include "Bismuth.h"

Bismuth::Bismuth(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	aabb = new Func_AABB;
	type = StudioProject::GEO_BISMUTH;
	aabb->setAABB_Static_Objects(pos, size, size, size);
	Bismuth_box = aabb->getAABB();
}
Bismuth::Bismuth(PlanetScene* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	myscene = scene;
	aabb = new Func_AABB;
	type = PlanetScene::GEO_BISMUTH;
	aabb->setAABB_Static_Objects(pos, size + 2, size + 5, size + 2);
	Bismuth_box = aabb->getAABB();
	isMined = false;
}
void Bismuth::interact()
{
	if (Application::IsKeyPressed('E') && !isMined)
	{
		/*unsigned textEnum = PlanetScene::GEO_TEXT;
		myscene->RenderTextOnScreen(myscene->meshList[textEnum], "Mine Bismuth [E]", Color(0, 1, 0), 2, 1, 4);*/
		Currency::get_instance()->add_mineral("bismuth");
		type = PlanetScene::GEO_ROCK;
		isMined = true;
	}
	//float x = ((ship->getter("position")).x - position.x);
	//float y = ((ship->getter("position")).y - position.y);
	//float z = 5.0f;

	//if (x < 10.0 && y < 10.0 && Application::IsKeyPressed('Z'))
	//{
	//	scale -= (z * myscene->_dt);
	//	if (scale < 1)
	//	{
	//		position.y += -500;
	//		myscene->BismuthValue += 1;
	//	}
	//}
}

AABB Bismuth::get_obj_AABB()
{
	return Bismuth_box;
}