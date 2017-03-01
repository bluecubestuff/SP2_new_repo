#include "Bismuth.h"

Bismuth::Bismuth(StudioProject* scene, Vector3 pos, float size) : ObjectRender(scene, pos, size)
{
	type = StudioProject::GEO_BISMUTH;
}
void Bismuth::interact()
{
	float x = ((ship->getter("position")).x - position.x);
	float y = ((ship->getter("position")).y - position.y);
	float z = 5.0f;

	if (x < 10.0 && y < 10.0 && Application::IsKeyPressed('Z'))
	{
		scale -= (z * myscene->_dt);
		if (scale < 1)
		{
			position.y += -500;
			myscene->BismuthValue += 1;
		}
	}
}