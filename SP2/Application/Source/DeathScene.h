#ifndef _DEATH_SCENE_H
#define _DEATH_SCENE_H

#include "Scene.h"

//Azimuth_Camera_System
#include "Camera2.h"
//FPS_Camera_System
#include "Camera3.h"

#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "playerShip.h"
#include "enemyShip.h"
#include "Missile.h"
#include "Func_AABB.h"
#include "DetectMemoryLeak.h"

#include <string>
#include <vector>
using std::vector;

class DeathScene : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,

		//basic shapes
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_RING,
		GEO_HEMISPHERE,
		GEO_SPHERE,
		GEO_LIGHTBALL,
		GEO_CYLINDER,

		//skybox
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		GEO_DEATHSCREEN,

		GEO_PLANET1,
		GEO_PLANET2,

		//text
		GEO_TEXT,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,

		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};

	MS modelStack, viewStack, projectionStack;
public:
	DeathScene();
	~DeathScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	bool bEnableLight = true;

	Light light[1];

	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderUI(Mesh* mesh, float x, float y, float sizex, float sizey);

	void RenderSkybox();
	char mapArray[100][100];

	Vector3 arrowPos;

	Camera camera;
	//Camera2 camera;
	//Camera3 camera;
};

#endif