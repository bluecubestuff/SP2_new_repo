#ifndef _PLANET_SCENE_H
#define _PLANET_SCENE_H

#include "Scene.h"

//Azimuth_Camera_System
#include "Camera2.h"
//3rd_Person_Camera_System
#include "Camera3.h"

#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "landPlayer.h"
#include "LandVehicle.h"
#include "Func_AABB.h"
#include "DetectMemoryLeak.h"
#include "CollisionManager.h"
#include "LandGenerate.h"
#include "ObjectFactory.h"
#include "landEnemy.h"
#include "ItemFactory.h"
#include "GalaxyGenerate.h"

#include <string>
#include <vector>
using std::vector;

//struct TAABB
//{
//	Vector3 pt_Max;
//	Vector3 pt_Min;
//};

class PlanetScene : public Scene
{
	friend class Rock;
	friend class Tree;
	friend class Mithril;
	friend class NPC;
	friend class Building;
	friend class ObjectRender;
	friend class Bismuth;
	friend class Iron;
	friend class Mithril;
	friend class Titanium;

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
		GEO_TITANIUM,
		GEO_IRON,
		GEO_BISMUTH,
		GEO_TREE,
		GEO_GOAT,
		GEO_NPC,
		GEO_BUILDING,
		GEO_ENEMY,
		GEO_ENEMY2,
		GEO_CAR,
		GEO_GOATGOAT,

		//Ships
		GEO_PLAYER_SHIP,

		//text
		GEO_TEXT,
		GEO_PLAYERBULLET,
		GEO_ENEMYBULLET,
		GEO_GUN,
		GEO_KNIFE,
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
	PlanetScene();
	~PlanetScene();

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

	int system_id; //id for the system player is at
	int planet_id; //id of the planet player is to enter
	char mapArray[100][100];

	CollisionManager* colManager;

	LandPlayer* Player;

	LandVehicle* Car;
	
	vector<LandEnemy*> meleeEnemies;

	vector<LandEnemy*> rangedEnemies;

	vector<LandEnemy*>::iterator it;

	//ObjectFactory objfactory;
	LandGenerate* gen;
	AABB BoundingBox;

	bool isExistingPlanet;
	bool isLeavingPlanet;
	//Camera2 camera;
	//Camera3 camera;
	Camera camera;
};

#endif