#include "ObjectRender.h"
#include "StudioProject.h"
#include "PlanetScene.h"

ObjectRender::ObjectRender(StudioProject* scene, Vector3 pos, float size)
{
	myscene = scene;
	position = pos;
	scale = size;
}
ObjectRender::ObjectRender(PlanetScene* scene, Vector3 pos, float size)
{
	planetScene = scene;
	position = pos;
	scale = size;
}
void ObjectRender::render()
{
	myscene->modelStack.PushMatrix();
	myscene->modelStack.Translate(position.x, position.y, position.z);
	myscene->modelStack.Scale(scale, scale, scale);
	myscene->RenderMesh(myscene->meshList[type], true);
	myscene->modelStack.PopMatrix();

}
void ObjectRender::render_planet()
{
	planetScene->modelStack.PushMatrix();
	planetScene->modelStack.Translate(position.x, position.y, position.z);
	planetScene->modelStack.Scale(scale, scale, scale);
	planetScene->RenderMesh(planetScene->meshList[type], true);
	planetScene->modelStack.PopMatrix();
}