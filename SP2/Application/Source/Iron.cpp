#include "Iron.h"

Iron::Iron(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	aabb = new Func_AABB;
	type = StudioProject::GEO_IRON;
	aabb->setAABB_Static_Objects(pos, size, size, size);
	Iron_box = aabb->getAABB();
}
Iron::Iron(PlanetScene* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	myscene = scene;
	aabb = new Func_AABB;
	type = PlanetScene::GEO_IRON;
	aabb->setAABB_Static_Objects(pos, size + 2, size + 5, size + 2);
	Iron_box = aabb->getAABB();
	isMined = false;
}
void Iron::interact()
{
	/*unsigned textEnum = PlanetScene::GEO_TEXT;
	myscene->RenderTextOnScreen(myscene->meshList[textEnum], "Mine Iron [E]", Color(0, 1, 0), 2, 1, 4);*/
	if (Application::IsKeyPressed('E') && !isMined)
	{
		Currency::get_instance()->add_mineral("iron");
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
	//		StudioProject::IronValue += 1;
	//	}
	//}
}

AABB Iron::get_obj_AABB()
{
	return Iron_box;
}
