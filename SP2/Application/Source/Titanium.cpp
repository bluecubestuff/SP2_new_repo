#include "Titanium.h"
#include "Currency.h"

Titanium::Titanium(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	type = StudioProject::GEO_TITANIUM;
	//aabb->setAABB_Static_Objects(pos, size);
}
Titanium::Titanium(PlanetScene* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	myscene = scene;
	aabb = new Func_AABB;
	type = PlanetScene::GEO_TITANIUM;
	aabb->setAABB_Static_Objects(pos, size + 2, size + 5, size + 2);
	Titanium_box = aabb->getAABB();
}
void Titanium::interact()
{
	/*unsigned textEnum = PlanetScene::GEO_TEXT;
	myscene->RenderTextOnScreen(myscene->meshList[textEnum], "Mine Titanium [E]", Color(0, 1, 0), 2, 1, 4);*/
	if (Application::IsKeyPressed('E'))
	{
		Currency::get_instance()->add_playerCurrency(8);
		type = PlanetScene::GEO_ROCK;
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
	//		myscene->TitaniumValue += 1;
	//	}
	//}
}

AABB Titanium::get_obj_AABB()
{
	return Titanium_box;
}
