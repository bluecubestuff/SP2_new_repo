#ifndef STUDIO_PROJECT_H
#define STUDIO_PROJECT_H

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
#include "LandGenerate.h"
#include "ObjectFactory.h"
#include "Bullet.h"
#include "SystemScene.h"
#include "SceneManager.h"
#include "Explosion.h"
#include "Currency.h"

#include <string>
#include <vector>

using std::vector;
using std::to_string;

//struct TAABB
//{
//	Vector3 pt_Max;
//	Vector3 pt_Min;
//};

class StudioProject : public Scene
{
	friend class Rock;
	friend class Tree;
	friend class Iron;
	friend class Titanium;
	friend class Mithril;
	friend class Bismuth;
	friend class NPC;
	friend class Building;
	friend class ObjectRender;

	enum GEOMETRY_TYPE
	{
		GEO_AXES,

		//basic shapes
		GEO_QUAD,
		GEO_CUBE,
		GEO_CUBE1,
		GEO_CUBE2,
		GEO_CIRCLE,
		GEO_RING,
		GEO_HEMISPHERE,
		GEO_SPHERE,
		GEO_LIGHTBALL,
		GEO_CYLINDER,

		//effects
		GEO_BULLET,
		GEO_EXPLOSION,

		//skybox
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		//objects
		GEO_ROCK,
		GEO_IRON,
		GEO_TITANIUM,
		GEO_MITHRIL,
		GEO_BISMUTH,
		GEO_TREE,
		GEO_GOAT,
		GEO_NPC,
		GEO_BUILDING,
		GEO_SPACE_STATION,
		//GEO_BULLET,

		//Planet
		GEO_DESERTPLANET,
		GEO_BLUEPLANET,
		GEO_GREENPLANET,

		//Ships
		GEO_PLAYER_SHIP,
		GEO_SHIELD,
		GEO_WAYPOINT,

		//text
		GEO_TEXT,

		//Mesh on Screen
		GEO_INVENTORY_BUTTON,
		GEO_INVENTORY_SCREEN,
		GEO_INVENTORY_SLOT,
		GEO_HEALTH_BAR,
		GEO_MP_BAR,

		GEO_HEALTH_FEEDBACK,
		GEO_SHIELD_FEEDBACK,

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
	StudioProject();
	~StudioProject();

	static PlayerShip* Player;

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
	bool inventorystate;
	float inventoryscreen;
	float _dt;
	static int IronValue;
	static int TitaniumValue;
	static int MithrilValue;
	static int BismuthValue;

	Light light[1];

	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderUI(Mesh* mesh, float x, float y, float sizex, float sizey);
	void RenderFeedback(Mesh* mesh, float x, float y, float sizex, float sizey);
	void RenderWaypoint(Mesh* mesh, float x, float y, float sizex, float sizey);

	void RenderSkybox();
	void RenderInventory();
	void DisplayInventory();
	void DisplayUI();

	char mapArray[100][100];
	
	Func_AABB* checker;

	EnemyShip* Enemy;
	Explosion* Explode;

	vector<EnemyShip*> hostiles;
	vector<Missile*> missiles;
	vector<Bullet*> bullets;
	vector<Bullet*> enemyBullets;
	vector<Explosion*> explosions;

	LandGenerate* gen;
	Mtx44 waypoint;
	ObjectFactory objfactory;
	Mouse mice;

	//Camera2 camera;
	//Camera3 camera;
};

#endif