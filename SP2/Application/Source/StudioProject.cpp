#include "StudioProject.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "Weapon.h"

//#include "LandGenerate.h"
#include <iostream>

Vector3 planeting(0, 2000, 1500);
Vector3 stationing(-500, 2000, 500);
float rotatePlanet = 0;

int StudioProject::IronValue = 1;
int StudioProject::TitaniumValue = 1;
int StudioProject::MithrilValue = 1;
int StudioProject::BismuthValue = 1;

PlayerShip* StudioProject::Player = NULL;

StudioProject::StudioProject() :objfactory(this)
{
	Player = new PlayerShip;
}

StudioProject::~StudioProject()
{
	delete this;
}

void StudioProject::Init()
{
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);

	//Enable depth buffer and depth testing
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ShowCursor(false);

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	//================================================================================================
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
	//================================================================================================

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	// Use our shader
	glUseProgram(m_programID);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	//variable to rotate geometry

	//Initialize camera settings
	//camera.Init(Vector3(1000, 950, 1010), Vector3(1000, 950, 1000), Vector3(0, 1, 0));

	//meshes------------------------------------------------------------------------------------------
	//meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	//=============================================================================
	waypoint = Mtx44(20, 0, 0, 0, 0, 20, 0, 0, 0, 0, 20, 0, 800, 700, 0, 1);
	gen = new LandGenerate(this);

	int test = 0;
	//Player = new PlayerShip(Vector3(0, 0, 1), Vector3(0, 1, 0), Vector3(1, 0, 0), Vector3(0, 0, 0), Vector3(0,0,0), 1.f, 100.f, 100.f, 1.f, 10.f);
	srand(time(NULL));
	int enemyQuantity = Math::RandIntMinMax(5, 10);
	for (int i = 0; i < enemyQuantity; i++)
	{
		Enemy = new EnemyShip(Vector3(0, 0, 1), Vector3(0, 1, 0), Vector3(1, 0, 0), Vector3(500, 2000, 1000 + i * 20), 40.f, 1.f, 10.f);
		hostiles.push_back(Enemy);
	}
	//=============================================================================

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 24, 13, 1);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 24, 13, 1);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//spaceBack.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//spaceFront.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//spaceLeft.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//spaceRight.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//spaceBottom.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//spaceTop.tga");

	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("Cube", Color(0.6f, 0.4f, 0.3f));

	meshList[GEO_PLAYER_SHIP] = MeshBuilder::GenerateOBJ("Player Ship", "OBJ//javShip.OBJ");
	meshList[GEO_PLAYER_SHIP]->textureID = LoadTGA("Image//shipTexture.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//SpaceFont.tga");

	meshList[GEO_GOAT] = MeshBuilder::GenerateOBJ("Player Ship", "OBJ//Missle.OBJ");

	meshList[GEO_BULLET] = MeshBuilder::GenerateOBJ("Player Ship", "OBJ//bullet_placeholder.OBJ");

	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("tree", "OBJ//tree.obj");
	meshList[GEO_ROCK] = MeshBuilder::GenerateOBJ("rock", "OBJ//rock.obj");

	meshList[GEO_SHIELD] = MeshBuilder::GenerateOBJ("Shieldza", "OBJ//sphere.obj");
	meshList[GEO_SHIELD]->textureID = LoadTGA("Image//shieldza.tga");

	meshList[GEO_CUBE] = MeshBuilder::GenerateOBJ("shield", "OBJ//shieldCubeThing.obj"); //ShieldCubeThing
	meshList[GEO_CUBE]->textureID = LoadTGA("Image//cubecube.tga");

	meshList[GEO_CUBE1] = MeshBuilder::GenerateOBJ("shield", "OBJ//shieldCubeThing.obj");
	meshList[GEO_CUBE1]->textureID = LoadTGA("Image//locked.tga");

	meshList[GEO_CUBE2] = MeshBuilder::GenerateOBJ("shield", "OBJ//shieldCubeThing.obj");
	meshList[GEO_CUBE2]->textureID = LoadTGA("Image//leedle.tga");

	meshList[GEO_WAYPOINT] = MeshBuilder::GenerateOBJ("waypoint", "OBJ//WaypointMarker.obj");
	meshList[GEO_WAYPOINT]->textureID = LoadTGA("Image//waypoint.tga");

	meshList[GEO_GREENPLANET] = MeshBuilder::GenerateOBJ("greenPlanet", "OBJ//Sphere2.OBJ");
	meshList[GEO_GREENPLANET]->textureID = LoadTGA("Image//GreenPlanet.tga");

	meshList[GEO_DESERTPLANET] = MeshBuilder::GenerateOBJ("desertPlanet", "OBJ//Sphere2.OBJ");
	meshList[GEO_DESERTPLANET]->textureID = LoadTGA("Image//DesertPlanet.tga");

	meshList[GEO_BLUEPLANET] = MeshBuilder::GenerateOBJ("bluePlanet", "OBJ//Sphere.OBJ");
	meshList[GEO_BLUEPLANET]->textureID = LoadTGA("Image//BluePlanet.tga");

	meshList[GEO_EXPLOSION] = MeshBuilder::GenerateOBJ("EXPLOSIONNN", "OBJ//Sphere.OBJ");
	meshList[GEO_EXPLOSION]->textureID = LoadTGA("Image//EXPLOSIONNN.tga");

	meshList[GEO_SPACE_STATION] = MeshBuilder::GenerateOBJ("Station", "OBJ//SpaceStation.OBJ");

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", Player->getter("right"), Player->getter("up"), Player->getter("forward"));



	meshList[GEO_INVENTORY_BUTTON] = MeshBuilder::GenerateOBJ("inventory", "OBJ//Inventory.obj");
	meshList[GEO_INVENTORY_BUTTON]->textureID = LoadTGA("Image//Inventory.tga");

	meshList[GEO_INVENTORY_SCREEN] = MeshBuilder::GenerateOBJ("inventory", "OBJ//InventoryScreen.obj");
	meshList[GEO_INVENTORY_SCREEN]->textureID = LoadTGA("Image//InventoryScreen.tga");

	meshList[GEO_IRON] = MeshBuilder::GenerateOBJ("iron", "OBJ//Iron.obj");
	meshList[GEO_IRON]->textureID = LoadTGA("Image//Iron.tga");

	meshList[GEO_TITANIUM] = MeshBuilder::GenerateOBJ("titanium", "OBJ//Titanium.obj");
	meshList[GEO_TITANIUM]->textureID = LoadTGA("Image//Titanium.tga");

	meshList[GEO_MITHRIL] = MeshBuilder::GenerateOBJ("mithril", "OBJ//Mithril.obj");
	meshList[GEO_MITHRIL]->textureID = LoadTGA("Image//Mithril.tga");

	meshList[GEO_BISMUTH] = MeshBuilder::GenerateOBJ("bismuth", "OBJ//Bismuth.obj");
	meshList[GEO_BISMUTH]->textureID = LoadTGA("Image//Bismuth.tga");

	meshList[GEO_INVENTORY_SLOT] = MeshBuilder::GenerateOBJ("inventory slot", "OBJ//InventorySlot.obj");
	meshList[GEO_INVENTORY_SLOT]->textureID = LoadTGA("Image//InventorySlot.tga");

	/*meshList[GEO_HEALTH_BAR] = MeshBuilder::GenerateOBJ("hp bar", "OBJ//HP.obj");
	meshList[GEO_HEALTH_BAR]->textureID = LoadTGA("Image//HP.tga");*/

	meshList[GEO_HEALTH_BAR] = MeshBuilder::GenerateOBJ("Health", "OBJ//HealthBar.obj");
	meshList[GEO_HEALTH_BAR]->textureID = LoadTGA("Image//blue-red.tga");

	meshList[GEO_SHIELD_BAR] = MeshBuilder::GenerateOBJ("Health", "OBJ//ShieldBar.obj");
	meshList[GEO_SHIELD_BAR]->textureID = LoadTGA("Image//blue-red.tga");

	meshList[GEO_HEALTH_FEEDBACK] = MeshBuilder::GenerateOBJ("Health Feedback", "OBJ//feedback.obj");
	meshList[GEO_HEALTH_FEEDBACK]->textureID = LoadTGA("Image//healthFeedback_2.tga");

	meshList[GEO_SHIELD_FEEDBACK] = MeshBuilder::GenerateOBJ("Shield Feedback", "OBJ//feedback.obj");
	meshList[GEO_SHIELD_FEEDBACK]->textureID = LoadTGA("Image//shieldFeedback_2.tga");

	meshList[GEO_HEALTH_SHIELD] = MeshBuilder::GenerateOBJ("HP & shield", "OBJ//HP.obj");
	meshList[GEO_HEALTH_SHIELD]->textureID = LoadTGA("Image//HP.tga");

	//------------------------------------------------------------------------------------------
	//light
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].LightPosition.Set(0, 1, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	//=============================================================================
	//light
	light[1].type = Light::LIGHT_POINT;
	light[1].LightPosition.Set(1000, 1000, 1000);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);
	//=============================================================================

	glUniform1i(m_parameters[U_NUMLIGHTS], 2);

	Mtx44 projection;
	projection.SetToPerspective(70.f, 16.f / 9.f, 0.1f, 5000.f);
	projectionStack.LoadMatrix(projection);

	inventorystate = false;
	bardecrease = 0;
	enemycount = enemyQuantity;
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void StudioProject::Update(double dt)
{
	_dt = dt;
	float LSPEED = 10.f;
	

	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	//light_controls---------------------------------------------------------------
	if (!Application::IsKeyPressed('I'))
	{
		inventorystate = true;
	}
	if (inventorystate && Application::IsKeyPressed('I'))
	{
		inventoryscreen = (inventoryscreen > 0) ? 0.0f : 2.0f;
		inventorystate = false;
	}

	//if (Application::IsKeyPressed('K'))
	//{
	//	light[1].LightPosition.z += (float)(LSPEED * dt);
	//}
	//if (Application::IsKeyPressed('J'))
	//	light[1].LightPosition.x -= (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('L'))
	//	light[1].LightPosition.x += (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('O'))
	//	light[1].LightPosition.y -= (float)(LSPEED * dt);
	//if (Application::IsKeyPressed('P'))
	//	light[1].LightPosition.y += (float)(LSPEED * dt);

	if (Application::IsKeyPressed('5'))
	{
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	//================================================================================
	//--------------------------------------------------------------------------------
	Player->Update(dt);
	Player->shieldUpdate(dt);
	Player->withinRange(hostiles);
	//Player->locking(hostiles[0]);

	for (auto &i : hostiles)
	{
		i->Update(dt, Player->getter("position"), Player->getter("forward"));
		i->shieldUpdate(dt);
		if (i->attack && i->fireRate > 0.2)
		{
			i->fireRate = 0;
			Bullet* bullet = new Bullet(i->getter("position"), i->getter("forward"), i->getter("up"), i->getter("right"));
			//meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", i->getter("forward"), i->getter("forward"), i->getter("forward") * 10);
			enemyBullets.push_back(bullet);
			//std::cout << i->getter("forward") << std::endl;
		}
	}
	static float fireRate = 0;
	fireRate += (float)dt;
	if (Application::IsKeyPressed(VK_LBUTTON) && fireRate > 1.f)
	{
		for (auto &i : hostiles)
		{
			//std::cout << i->locked << std::endl;
			if (i->locked)
			{
				Missile* missile = new Missile(Enemy, Player, 20.f, true);
				missiles.push_back(missile);
				fireRate = 0;
			}
		}
	}
	if (missiles.size() != 0)
		for (int i = 0; i < missiles.size(); i++)
		{
			for (auto &j : hostiles)
			{
				if (missiles.size() != 0 && i < missiles.size())
				{
					Vector3 temp;
					if (j->locked)
					{
						missiles[i]->checkTargets(hostiles);								//updates the missile to change target to enemy
						temp = missiles[i]->e->getter("position");
						missiles[i]->tracking(dt, missiles[i]->e->getter("position"));		//let the missiles translate and rotate to the enemy position.
					}
					if (j->getAABB()->pointInAABB(missiles[i]->getPos()))					//j->getAABB()->getAABB(),
					{
						Missile* temp = missiles[i];
						j->setHit();
						if (j->getSP() <= 0)
						{
							j->decreaseHealth(30);
						}
						else
						{
							j->decreaseShield(30);
						}

						j->agro = true;
						missiles.erase(missiles.begin() + i);
						delete temp;
					}
				}
				else
					break;
			}
		}

	for (auto &i : hostiles)
	{
		if (i->getHit())
		{
			static float cooldown = 0;
			cooldown += dt;
			if (cooldown > 0.5f)
			{
				i->setHit();
				cooldown = 0;
			}
		}
	}
	//======================================================================================
	//bullet
	if (Application::IsKeyPressed(VK_RBUTTON))
	{
		//for (auto &i : hostiles)
		//{
		//	if (i->getTargeted())
		//	{
		//		//bullet travels 200 unit persecond;
		//		//enemy translate at variable speed
		//		i->getSpeed();
		//	}
		//}
		Bullet* bullet = new Bullet(Player->getter("position"), Player->getter("forward"), Player->getter("up"), Player->getter("right"));
		bullets.push_back(bullet);
	}
	//std::cout << bullets.size() << std::endl;
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update(dt);
		for (auto &j : hostiles)
		{
			if (i < bullets.size())
			{
				if (j->getAABB()->pointInAABB(bullets[i]->getPos()))
				{
					Bullet* temp = bullets[i];
					j->setHit();
					if (j->getSP() <= 0)
					{
						j->decreaseHealth(1);
					}
					else
					{
						j->decreaseShield(1);
					}
					j->agro = true;
					bullets.erase(bullets.begin() + i);
					delete temp;
					i = 0;
				}
			}
			else
				i = 0;
		}
		if (i < bullets.size() && bullets[i]->outOfRange)
		{
			Bullet* temp = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete temp;
			i = 0;
		}
	}

	for (int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBullets[i]->Update(dt);
		if (Player->getAABB()->pointInAABB(enemyBullets[i]->getPos()))
		{
			Bullet* temp = enemyBullets[i];
			if (Player->getSP() <= 0)
			{
				Player->decreaseHealth(1);
				Player->damageT = 1;
				Player->damaged = true;
				//std::cout << "enemy hit us" << std::endl;
			}
			else
			{
				Player->decreaseShield(1);
				Player->damageT = 1;
				Player->damaged = true;
			}
			
			enemyBullets.erase(enemyBullets.begin() + i);
			delete temp;
			i = 0;
		}
		if (i < enemyBullets.size() && enemyBullets[i]->outOfRange)
		{
			Bullet* temp = enemyBullets[i];
			enemyBullets.erase(enemyBullets.begin() + i);
			delete temp;
			i = 0;
		}
	}

	Player->damageT -= dt;
	if (Player->damageT < 0)
	{
		Player->damaged = false;
	}

	for (int i = 0; i < hostiles.size(); i++)
	{
		if (hostiles[i]->getHP() <= 0)
		{
			//EnemyShip* dadad = hostiles[i];
			Currency::get_instance()->value_adder(2);
			hostiles[i]->deaded = true;
			Explode = new Explosion(hostiles[i]->getter("position"));
			hostiles.erase(hostiles.begin() + i);
			explosions.push_back(Explode);
			i = 0;
			enemycount -= 1;
		}
		//std::cout << "S: " << hostiles[i]->getSP() << " H: " << hostiles[i]->getHP() << std::endl;
	}

	//std::cout << Currency::get_instance()->value_getter() << std::endl;

	for (auto &i : hostiles)
	{
		if (i->getTargeted())
		{
			Vector3 wForward;
			Vector3 wRight;
			Vector3 wUp;
			Vector3 target;
			Vector3 pos = Player->getter("position") + Player->getter("forward") + Player->getter("up") * 0.5;
			if (Player->firstThird == true)
			{
				target = ((i->getter("position") - Player->Camera->position).Normalized());
			}
			else
			{
				target = ((i->getter("position") - Player->ThirdCamera->position).Normalized());
			}
			wForward = target;
			try
			{
				wUp = wForward.Cross(Player->getter("right")).Normalized();
			}
			catch (std::exception &e)
			{
				wUp = Player->getter("up");
				std::cout << "divide by zero in waypoint" << std::endl;
				//divide by zero error
			}
			wRight = wForward.Cross(wUp);
			wForward.Normalize();
			wRight.Normalize();
			wUp.Normalize();
			//std::cout << wRight.Length() << std::endl;
			waypoint = Mtx44(wRight.x, wRight.y, wRight.z, 0, wUp.x, wUp.y, wUp.z, 0, wForward.x, wForward.y, wForward.z, 0, pos.x, pos.y, pos.z, 1);
			//meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", wRight, wUp, wForward);
		}
	}

	for (int i = 0; i < explosions.size(); i++)
	{
		explosions[i]->Update(dt);
		if (explosions[i]->getDone())
		{
			Explosion* temp = explosions[i];
			explosions.erase(explosions.begin() + i);
			delete temp;
			i = 0;
		}
	}

	if ((planeting - Player->getter("position")).Length() < 500) //planet
	{
		SceneManager::get_instance()->SceneSelect(3);
	}

	if ((stationing - Player->getter("position")).Length() < 500) //space station
	{
		SceneManager::get_instance()->SceneSelect(6);
		//std::cout << "stationingly" << std::endl;
	}

	//placeholder
	if (Player->getHP() <= 0)
	{
		
		SceneManager::get_instance()->setPrevSceneID(2);
		SceneManager::get_instance()->SceneSelect(7);
	}

	rotatePlanet += dt;
	std::cout << Player->getter("position") << std::endl;

	if (Player->getter("position").x > 2000 || Player->getter("position").z > 2000
		|| Player->getter("position").x < -200 || Player->getter("position").z < 0)
	{
		SceneManager::get_instance()->SceneSelect(4);
	}
	//camera.Update(dt);
}

void StudioProject::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 MVP;


	viewStack.LoadIdentity();

	if (Player->firstThird)
	{
		viewStack.LookAt(Player->Camera->position.x, Player->Camera->position.y,
			Player->Camera->position.z, Player->Camera->target.x, Player->Camera->target.y,
			Player->Camera->target.z, Player->Camera->up.x, Player->Camera->up.y, Player->Camera->up.z);
	}
	else
	{
		viewStack.LookAt(Player->ThirdCamera->position.x, Player->ThirdCamera->position.y,
			Player->ThirdCamera->position.z, Player->ThirdCamera->target.x, Player->ThirdCamera->target.y,
			Player->ThirdCamera->target.z, Player->ThirdCamera->up.x, Player->ThirdCamera->up.y, Player->ThirdCamera->up.z);
	}


	Position lightPosition_cameraspace = viewStack.Top() * light[0].LightPosition;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	//===================================================================================
	Position lightPosition_cameraspace2 = viewStack.Top() * light[1].LightPosition;//test
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace2.x);//test
	//===================================================================================

	modelStack.LoadIdentity();
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	//=====================================================================================
	if (light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].LightPosition.x, light[1].LightPosition.y, light[1].LightPosition.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	if (light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].LightPosition;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	if (light[1].type == Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].LightPosition;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}
	//=======================================================================================

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].LightPosition.x, light[0].LightPosition.y, light[0].LightPosition.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	if (light[0].type == Light::LIGHT_SPOT)//else if
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].LightPosition;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	if (light[0].type == Light::LIGHT_POINT)//else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].LightPosition;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}


	modelStack.PushMatrix();
	modelStack.LoadMatrix(Player->getStamp());
	RenderMesh(meshList[GEO_PLAYER_SHIP], true);
	modelStack.PopMatrix();

	for (auto &i : missiles)
	{
		modelStack.PushMatrix();
		modelStack.LoadMatrix(i->Stamp);
		RenderMesh(meshList[GEO_GOAT], true);
		modelStack.PopMatrix();
	}

	for (auto &i : bullets)
	{
		modelStack.PushMatrix();
		modelStack.LoadMatrix(i->getMatrix());
		RenderMesh(meshList[GEO_BULLET], false);
		modelStack.PopMatrix();
	}

	for (auto &i : enemyBullets)
	{
		modelStack.PushMatrix();
		modelStack.LoadMatrix(i->getMatrix());
		RenderMesh(meshList[GEO_BULLET], false);
		modelStack.PopMatrix();
	}
	
	RenderSkybox();

	//=================================================================================================
	/*modelStack.PushMatrix();
	modelStack.Translate(light[0].LightPosition.x, light[0].LightPosition.y, light[0].LightPosition.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[1].LightPosition.x, light[1].LightPosition.y, light[1].LightPosition.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();*/
	//===================================================================================================
	
	/*modelStack.PushMatrix();
	modelStack.Translate(Player->getter("position").x, Player->getter("position").y, Player->getter("position").z);
	modelStack.Translate(Player->getter("forward").x, Player->getter("forward").y, Player->getter("forward").z);
	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();*/

	modelStack.PushMatrix();
	modelStack.LoadMatrix(waypoint);
	RenderMesh(meshList[GEO_WAYPOINT], true);
	modelStack.PopMatrix();
	//generate the planet to land on
	modelStack.PushMatrix();
	modelStack.Translate(0, 2000, 1500);
	modelStack.Scale(500, 500, 500);
	modelStack.Rotate(rotatePlanet, 0, 1, 0);

	switch (SystemScene::planet)
	{
	case 1:
		RenderMesh(meshList[GEO_GREENPLANET], true);
		break;
	case 2:
		RenderMesh(meshList[GEO_DESERTPLANET], true);
		break;
	case 3:
		RenderMesh(meshList[GEO_BLUEPLANET], true);
		break;
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-500, 2000, 500);
	modelStack.Scale(30, 30, 30);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_SPACE_STATION], true);
	modelStack.PopMatrix();

	for (auto &i : hostiles)
	{
		modelStack.PushMatrix();
		modelStack.LoadMatrix(i->getStamp());
		RenderMesh(meshList[GEO_PLAYER_SHIP], true);
		//RenderMesh(meshList[GEO_AXES], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		if (i->getHit())
		{
			if (i->getSP() > 0)
			{
				modelStack.Translate(i->getter("position").x, i->getter("position").y, i->getter("position").z);
				modelStack.Scale(i->getSize() * 3, i->getSize() * 3, i->getSize() * 3);
				RenderMesh(meshList[GEO_SHIELD], false);
			}
			else
			{
				RenderUI(meshList[GEO_CUBE1], 800, 450, 35, 35);
			}
		}
		if (i->locked)
		{
			modelStack.Translate(i->getter("position").x, i->getter("position").y, i->getter("position").z);
			modelStack.Scale(i->getSize() * 5, i->getSize() * 5, i->getSize() * 5);
			RenderMesh(meshList[GEO_CUBE1], false);
		}
		if (i->getTargeted())
		{
			modelStack.Translate(i->getter("position").x, i->getter("position").y, i->getter("position").z);
			modelStack.Scale(i->getSize() * 6, i->getSize() * 6, i->getSize() * 6);
			RenderMesh(meshList[GEO_CUBE], false);
		}

		modelStack.PushMatrix();
		modelStack.Translate(i->getter("position").x, i->getter("position").y, i->getter("position").z);
		modelStack.Scale(i->getSize() * 6, i->getSize() * 6, i->getSize() * 6);
		RenderMesh(meshList[GEO_CUBE2], false);
		modelStack.PopMatrix();

		modelStack.PopMatrix();
	}

	for (auto &i : explosions)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i->getPos().x, i->getPos().y, i->getPos().z);
		modelStack.Scale(i->getScale(), i->getScale(), i->getScale());
		RenderMesh(meshList[GEO_EXPLOSION], false);
		modelStack.PopMatrix();
	}
	//if (SystemScene::planet > 0)
	//{
	//	std::cout << SystemScene::planet << std::endl;
	//}
	//gen->BuildLand();
	if (Player->firstThird)
	{
		Mouse mouse;
		POINT point = mouse.freeMouse();
		modelStack.PushMatrix();
		RenderUI(meshList[GEO_SPHERE], point.x, point.y, 5, 5);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		RenderUI(meshList[GEO_SPHERE], 800, 450, 3, 3);
		modelStack.PopMatrix();
	}
	//RenderUI(meshList[GEO_INVENTORY_BUTTON], 15.0, 15.0, 2.0, 2.0);//Inventory Button

	//objfactory.createObject(new Rock(this, Vector3(10, 50, 10), 3));
	objfactory.renderObjects(1);
	objfactory.interactObjects();
	

	modelStack.PushMatrix();

	if (Player->damaged && Player->getSP() > 0)
	{
		RenderFeedback(meshList[GEO_SHIELD_FEEDBACK], 800, 450, 1600, 900);
		//std::cout << "shield Damaged" << std::endl;
	}
	else if (Player->damaged && Player->getHP())
	{
		RenderFeedback(meshList[GEO_HEALTH_FEEDBACK], 800, 450, 1600, 900);
		//std::cout << "health Damaged" << std::endl;
	}
	DisplayUI();
	modelStack.PopMatrix();

	//RenderFeedback(meshList[GEO_HEALTH_FEEDBACK], 800, 450, 100, 100);
}

void StudioProject::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (Application::IsKeyPressed('9'))
	{
		bEnableLight = false;
	}
	if (Application::IsKeyPressed('0'))
	{
		bEnableLight = true;
	}
	if (enableLight && bEnableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void StudioProject::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void StudioProject::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);

	Mtx44 ortho;
	ortho.SetToOrtho(0, 1600, 0, 900, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.8f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	//Add these code just before glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

//============================================TESTING===============================================
void StudioProject::RenderUI(Mesh* mesh, float x, float y, float sizex, float sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 1600, 0, 900, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	//scale and translate accordingly
	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizex, sizey, 1);
	RenderMesh(mesh, false); //UI should not have light

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void StudioProject::RenderFeedback(Mesh* mesh, float x, float y, float sizex, float sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 1600, 0, 900, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	//scale and translate accordingly
	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizex, sizey, 1);
	RenderMesh(mesh, false); //UI should not have light

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

//============================================TESTING===============================================
void StudioProject::RenderWaypoint(Mesh* mesh, float x, float y, float sizex, float sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 1600, 0, 900, -100, 100); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	//scale and translate accordingly
	modelStack.LoadMatrix(waypoint);
	RenderMesh(mesh, true); //UI should not have light

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}
//=================================================================================================

void StudioProject::RenderSkybox()
{
	modelStack.PushMatrix();//push ground
	modelStack.Translate(950, 0, 950);
	modelStack.Scale(2, 2, 2);

	modelStack.PushMatrix();//seperate from ground

	modelStack.PushMatrix();//push top
	modelStack.Translate(0, 1995, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(2000, 1, 2000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();//end top

	modelStack.PushMatrix();//push back
	modelStack.Translate(0, 997, 997);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2000, 1, 2000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();//end back

	modelStack.PushMatrix();//push front
	modelStack.Translate(0, 997, -997);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(2000, 1, 2000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();//end front

	modelStack.PushMatrix();//push left
	modelStack.Translate(997, 997, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(2000, 1, 2000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();//end left

	modelStack.PushMatrix();//push right
	modelStack.Translate(-997, 997, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(2000, 1, 2000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();//end right

	modelStack.PopMatrix();//end speration

	modelStack.Translate(0, 0, 0);
	modelStack.Scale(2000, 1, 2000);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();//end ground
}

void StudioProject::DisplayInventory()
{
	//string test = "test = ABCDEFGHIJK";

	if (IronValue > 0)
	{
		RenderTextOnScreen(meshList[StudioProject::GEO_TEXT], (to_string(IronValue)), Color(1, 1, 1), 2, 35.85, 9.2);
		RenderUI(meshList[GEO_IRON], 1400.0, 800.0, 6, 6);//Iron Symbol
		//RenderTextOnScreen(meshList[StudioProject::GEO_TEXT], test, Color(1, 1, 1), 2, 30, 10);
	}
	if (TitaniumValue > 0)
	{
		RenderTextOnScreen(meshList[StudioProject::GEO_TEXT], (to_string(TitaniumValue)), Color(1, 1, 1), 2, 35.85, 14.2);
		RenderUI(meshList[GEO_TITANIUM], 70.0, 30.0, 0.5, 0.5);//Titanium Symbol
	}
	if (MithrilValue > 0)
	{
		RenderTextOnScreen(meshList[StudioProject::GEO_TEXT], (to_string(MithrilValue)), Color(1, 1, 1), 2, 35.85, 19.2);
		RenderUI(meshList[GEO_MITHRIL], 70.0, 40.0, 0.5, 0.5);//Mithril Symbol
	}
	if (BismuthValue > 0)
	{
		RenderTextOnScreen(meshList[StudioProject::GEO_TEXT], (to_string(BismuthValue)), Color(1, 1, 1), 2, 35.85, 24.2);
		RenderUI(meshList[GEO_BISMUTH], 70.0, 50.0, 0.5, 0.5);//Bismuth Symbol
	}
}

void StudioProject::DisplayUI()
{
	//RenderTextOnScreen(meshList[StudioProject::GEO_TEXT], "test,test,test", Color(1, 1, 1), 50, 5, 5);
	RenderTextOnScreen(meshList[StudioProject::GEO_TEXT], (to_string((int)Player->getHP())), Color(1, 0, 0), 25, 25, 30.5); 
	RenderTextOnScreen(meshList[StudioProject::GEO_TEXT], (to_string((int)Player->getSP())), Color(0, 0, 1), 25, 25, 29.5);
	RenderTextOnScreen(meshList[StudioProject::GEO_TEXT], (to_string(enemycount)), Color(0, 0, 1), 25, 40, 29.5);
	if (inventoryscreen > 0)
	{
		//RenderUI(meshList[GEO_INVENTORY_SCREEN], 40.0, 30.0, 3.0, 3.0);//Inventory Screen
		RenderUI(meshList[GEO_INVENTORY_SLOT], 70.0, 20.0, 0.75, 0.75);//Inventory Slot
		RenderUI(meshList[GEO_INVENTORY_SLOT], 70.0, 30.0, 0.75, 0.75);//Inventory Slot
		RenderUI(meshList[GEO_INVENTORY_SLOT], 70.0, 40.0, 0.75, 0.75);//Inventory Slot
		RenderUI(meshList[GEO_INVENTORY_SLOT], 70.0, 50.0, 0.75, 0.75);//Inventory Slot
		DisplayInventory(); //minerals
	}
	RenderUI(meshList[GEO_HEALTH_SHIELD], 250, 750, 20, 20); //Outline

	bardecrease = Player->hull->getHullPoint();

	RenderUI(meshList[GEO_HEALTH_BAR], 230, 768, (360 * (Player->getHP() / bardecrease)), 16);//health bar

	bardecrease = Player->shield->getShieldPoint();

	RenderUI(meshList[GEO_SHIELD_BAR], 232, 738, (360 * (Player->getSP() / bardecrease)), 16);//shield bar
}
//bool StudioProject::pointInAABB(const TAABB& box, const Vector3& point)//test
//{
//	if ((point.x > box.pt_Min.x && point.x < box.pt_Max.x)
//		&& (point.z < box.pt_Min.z && point.z > box.pt_Max.z))
//	{
//		return true;
//	}
//
//	return false;
//}
//
//bool StudioProject::AABBtoAABB(const TAABB& box01, const TAABB& box02)
//{
//	if (box01.pt_Max.x > box02.pt_Min.x && box01.pt_Min.x < box02.pt_Max.x &&
//		box01.pt_Max.y > box02.pt_Min.y && box01.pt_Min.y < box02.pt_Max.y &&
//		box01.pt_Max.z < box02.pt_Min.z && box01.pt_Min.z > box02.pt_Max.z)
//	{
//		return true;
//	}
//
//	return false;
//}
void StudioProject::Exit()
{ 
	for (auto &i : hostiles)
	{
		delete i;
	}
	for (auto &i : missiles)
	{
		delete i;
	}
	hostiles.clear();
	missiles.clear();
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}