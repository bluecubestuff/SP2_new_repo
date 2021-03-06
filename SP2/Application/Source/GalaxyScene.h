#ifndef _GALAXY_SCENE_H
#define _GALAXY_SCENE_H

#include "Scene.h"

//Azimuth_Camera_System
#include "Camera2.h"
//3rd_Person_Camera_System
#include "Camera3.h"

#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Func_AABB.h"
#include "DetectMemoryLeak.h"
#include "CollisionManager.h"
#include "ObjectFactory.h"
#include "SystemTravelShip.h"
#include "GalaxyGenerate.h"

#include <string>
#include <vector>
using std::vector;

class GalaxyScene : public Scene
{
	friend class Rock;
	friend class Tree;
	friend class Mithril;
	friend class NPC;
	friend class Building;
	friend class ObjectRender;
	friend class OrbitLine;
	friend class GreenPlanet;
	friend class DesertPlanet;
	friend class BluePlanet;
	friend class Sun; 

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

		//objects
		GEO_ROCK,
		GEO_MITHRIL,
		GEO_TREE,
		GEO_GOAT,
		GEO_NPC,
		GEO_BUILDING,
		GEO_GRID,
		GEO_HUD,
		//Ships
		GEO_PLAYER_SHIP,
		GEO_SUN,
		GEO_ORBIT_LINES,
		GEO_GREENPLANET,
		GEO_DESERTPLANET,
		GEO_BLUEPLANET,

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

		//================================================================================================
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		//================================================================================================

		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};

	MS modelStack, viewStack, projectionStack;
public:
	GalaxyScene();
	~GalaxyScene();

	SystemTravelShip* Player;
	float rotate;

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

	bool isPointingToSystem;
	char mapArray[100][100];

	//ObjectFactory objfactory;
	GalaxyGenerate *galaxy_gen;
	//CollisionManager* system_collision;

	int move_along_x, move_along_y;
	string x_pos, y_pos;
	//Camera2 camera;
	//Camera3 camera;
	Camera camera;
};

#endif