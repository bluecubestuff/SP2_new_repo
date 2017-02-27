#include "ObjectRender.h"
#include "StudioProject.h"
#include "PlanetScene.h"
#include "SystemScene.h"
#include "GalaxyScene.h"

ObjectRender::ObjectRender(StudioProject* scene, Vector3 pos, float size)
{
	myscene = scene;
	position = pos;
	scale = size;
}
ObjectRender::ObjectRender(PlanetScene* scene, Vector3 pos, float size)
{
	planetscene = scene;
	position = pos;
	scale = size;
}
ObjectRender::ObjectRender(SystemScene* scene, Vector3 pos, float sizeX, float sizeY, float aRotate, float pRotate)
{
	this->systemscene = scene;
	this->position = pos;
	this->scaleX = sizeX;
	this->scaleZ = sizeY;
	this->aroundRotate = aRotate;
	this->planetRotate = pRotate;
}
ObjectRender::ObjectRender(GalaxyScene* scene, Vector3 pos, float sizeX, float sizeY, float aRotate, float pRotate)
{
	this->galaxyscene = scene;
	this->position = pos;
	this->scaleX = sizeX;
	this->scaleZ = sizeY;
	this->aroundRotate = aRotate;
	this->planetRotate = pRotate;
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
	planetscene->modelStack.PushMatrix();
	planetscene->modelStack.Translate(position.x, position.y, position.z);
	planetscene->modelStack.Scale(scale, scale, scale);
	planetscene->RenderMesh(planetscene->meshList[type], true);
	planetscene->modelStack.PopMatrix();
}

void ObjectRender::render_system_planets(float aRotate,float pRotate)
{	//for system only
	systemscene->modelStack.PushMatrix();
	systemscene->modelStack.Rotate(aRotate * aroundRotate, 0, 0, 1);
	systemscene->modelStack.Scale(scaleX, 1, scaleZ);
	systemscene->modelStack.Translate(position.x, 0, 0);
	systemscene->modelStack.Rotate(pRotate * planetRotate, 0, 0, 1);
	systemscene->RenderMesh(systemscene->meshList[type], false);
	systemscene->modelStack.PopMatrix();
}