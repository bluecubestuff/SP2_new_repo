#include "PlanetScene.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "SystemScene.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "SceneManager.h"
#include "Currency.h"
//#include "LandGenerate.h"
#include <iostream>

ItemFactory* ItemFactory::instance = 0;

PlanetScene::PlanetScene()
{
}

PlanetScene::~PlanetScene()
{
}

void PlanetScene::Init()
{
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

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

	Player = new LandPlayer(Vector3(1000, 3, 1000), Vector3(0, 0, 1), Vector3(1, 0, 0), 100.f);

	gen = new LandGenerate(this);  
	/*Enemy = new LandEnemy(Vector3(600, 0, 500), 69.f, 5.f );*/
	colManager = new CollisionManager;
	Car = new LandVehicle;
	//=============================================================================

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 24, 13, 1);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 24, 13, 1);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	if (SystemScene::planet == 1)
	{
		meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
	}
	if (SystemScene::planet == 3)
	{
		meshList[GEO_FRONT]->textureID = LoadTGA("Image//craterlake_ft.tga");
	}
	if (SystemScene::planet == 2)
	{
		meshList[GEO_FRONT]->textureID = LoadTGA("Image//nevada_ft.tga");
	}

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	if (SystemScene::planet == 1)
	{
		meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");
	}
	if (SystemScene::planet == 3)
	{
		meshList[GEO_BACK]->textureID = LoadTGA("Image//craterlake_bk.tga");
	}
	if (SystemScene::planet == 2)
	{
		meshList[GEO_BACK]->textureID = LoadTGA("Image//nevada_bk.tga");
	}

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	if (SystemScene::planet == 1)
	{
		meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
	}
	if (SystemScene::planet == 3)
	{
		meshList[GEO_LEFT]->textureID = LoadTGA("Image//craterlake_lf.tga");
	}
	if (SystemScene::planet == 2)
	{
		meshList[GEO_LEFT]->textureID = LoadTGA("Image//nevada_lf.tga");
	}

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	if (SystemScene::planet == 1)
	{
		meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");
	}
	if (SystemScene::planet == 3)
	{
		meshList[GEO_RIGHT]->textureID = LoadTGA("Image//craterlake_rt.tga");
	}
	if (SystemScene::planet == 2)
	{
		meshList[GEO_RIGHT]->textureID = LoadTGA("Image//nevada_rt.tga");
	}

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	if (SystemScene::planet == 1)
	{
		meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");
	}
	if (SystemScene::planet == 3)
	{
		meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//craterlake_dn.tga");
	}
	if (SystemScene::planet == 2)
	{
		meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//nevada_dn.tga");
	}

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	if (SystemScene::planet == 1)
	{
		meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
	}
	if (SystemScene::planet == 3)
	{
		meshList[GEO_TOP]->textureID = LoadTGA("Image//craterlake_up.tga");
	}
	if (SystemScene::planet == 2)
	{
		meshList[GEO_TOP]->textureID = LoadTGA("Image//nevada_up.tga");
	}

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("Cube", Color(0.6f, 0.4f, 0.3f));

	meshList[GEO_CAR] = MeshBuilder::GenerateOBJ("Player Ship", "OBJ//hovercar.OBJ");
	meshList[GEO_CAR]->textureID = LoadTGA("Image//hovercar.tga");

	meshList[GEO_PLAYER_SHIP] = MeshBuilder::GenerateOBJ("Player Ship", "OBJ//playerShip.OBJ");
	meshList[GEO_PLAYER_SHIP]->textureID = LoadTGA("Image//playerShip.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_GOAT] = MeshBuilder::GenerateOBJ("Player Ship", "OBJ//tree.OBJ");

	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("tree", "OBJ//tree.obj");
	meshList[GEO_TREE]->textureID = LoadTGA("Image//tree.tga");

	meshList[GEO_ROCK] = MeshBuilder::GenerateOBJ("rock", "OBJ//rock.obj");
	meshList[GEO_ROCK]->textureID = LoadTGA("Image//rock.tga");

	meshList[GEO_ENEMY] = MeshBuilder::GenerateOBJ("meleeEnemy", "OBJ//meleeEnemy.OBJ");
	meshList[GEO_ENEMY]->textureID = LoadTGA("Image//meleeEnemy.tga");
	meshList[GEO_ENEMY2] = MeshBuilder::GenerateOBJ("rangedEnemy", "OBJ/rangedEnemy.OBJ");
	meshList[GEO_ENEMY2]->textureID = LoadTGA("Image//rangedEnemy.tga");

	meshList[GEO_PLAYERBULLET] = MeshBuilder::GenerateOBJ("bullet", "OBJ//playerProjectile.OBJ");
	meshList[GEO_PLAYERBULLET]->textureID = LoadTGA("Image//playerProjectile.tga");
	
	meshList[GEO_KNIFE] = MeshBuilder::GenerateOBJ("gun", "OBJ//knife.OBJ");
	meshList[GEO_KNIFE]->textureID = LoadTGA("Image//knife.tga");

	meshList[GEO_GUN] = MeshBuilder::GenerateOBJ("gun", "OBJ//gun.OBJ");
	meshList[GEO_GUN]->textureID = LoadTGA("Image//gun.tga");

	meshList[GEO_ENEMYBULLET] = MeshBuilder::GenerateOBJ("bullet", "OBJ//enemyProjectile.OBJ");
	meshList[GEO_ENEMYBULLET]->textureID = LoadTGA("Image//enemyProjectile.tga");

	meshList[GEO_GOATGOAT] = MeshBuilder::GenerateOBJ("goat", "OBJ//goat_easter_egg.obj");

	meshList[GEO_IRON] = MeshBuilder::GenerateOBJ("iron", "OBJ//rock.obj");
	meshList[GEO_IRON]->textureID = LoadTGA("Image//IronTexture.tga");

	meshList[GEO_MITHRIL] = MeshBuilder::GenerateOBJ("tree", "OBJ//rock.obj");
	meshList[GEO_MITHRIL]->textureID = LoadTGA("Image//MithrilTexture.tga");

	meshList[GEO_TITANIUM] = MeshBuilder::GenerateOBJ("tree", "OBJ//rock.obj");
	meshList[GEO_TITANIUM]->textureID = LoadTGA("Image//TitaniumTexture.tga");

	meshList[GEO_BISMUTH] = MeshBuilder::GenerateOBJ("tree", "OBJ//rock.obj");
	meshList[GEO_BISMUTH]->textureID = LoadTGA("Image//BismuthTexture.tga");
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

	/*Enemy->enemyInit(gen->path, Enemy->Position, Vector3(800, 650));
	landEnemies.push_back(Enemy);*/

	isExistingPlanet = false;

	system_id = GalaxyGenerate::get_instance()->galaxy_id_getter();
	planet_id = GalaxyGenerate::get_instance()->planet_id_getter();

	for (int i = 0; i < GalaxyGenerate::get_instance()->system_database[system_id]->land_database.size(); i++)
	{
		if (GalaxyGenerate::get_instance()->system_database[system_id]->land_database.count(planet_id))
		{
			isExistingPlanet = true;
			break;
		}
	}

	if (!isExistingPlanet)
	{
		gen->landInIt();
		gen->saveLandInIt();
	}
	
	//for (int i = 0; i <= gen->noOfEnemies; i++)
	//{
	//	if (gen->enemy_type[i] == 1)
	//	{
	//		LandEnemy* Enemy = new LandEnemy(gen->enemy_positions[i], gen->enemy_goal[i], 100, 3);
	//		meleeEnemies.push_back(Enemy);
	//	}
	//	else if (gen->enemy_type[i] == 2)
	//	{
	//		LandEnemy* Enemy = new LandEnemy(gen->enemy_positions[i], gen->enemy_goal[i], 100, 3);
	//		rangedEnemies.push_back(Enemy);
	//	}
	//}

	//for (it = meleeEnemies.begin(); it != meleeEnemies.end(); it++)
	//{
	//	(*it)->enemyInit(gen->path, (*it)->Position, (*it)->enemyGoal);
	//}

	//for (it = rangedEnemies.begin(); it != rangedEnemies.end(); it++)
	//{
	//	(*it)->enemyInit(gen->path, (*it)->Position, (*it)->enemyGoal);
	//}
 
	isLeavingPlanet = false;

	BoundingBox.pt_Min.Set(0,5,0);
	BoundingBox.pt_Min.Set(2500, 100, 2500);

	//ItemFactory::get_instance()->randomlyCreateWeapon();
	//std::cout << "weapon name: " << ItemFactory::get_instance()->weapon_storage_getter()[0]->getName() << "\n";
	//std::cout << "weapon dmg: " << ItemFactory::get_instance()->weapon_storage_getter()[0]->getWeaponDamage() << "\n";
	//std::cout << "weapon value: " << ItemFactory::get_instance()->weapon_storage_getter()[0]->getValue() << "\n";
	//std::cout << "weapon durability: " << ItemFactory::get_instance()->weapon_storage_getter()[0]->getDurability() << "\n";

	//camera.Init(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void PlanetScene::Update(double dt)
{
	float LSPEED = 10.f;
	//meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", Player->getter("right"), Player->getter("up"), Player->getter("forward"));

	//if (Application::IsKeyPressed('1')) //enable back face culling
	//	glEnable(GL_CULL_FACE);
	//if (Application::IsKeyPressed('2')) //disable back face culling
	//	glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	//light_controls---------------------------------------------------------------
	if (Application::IsKeyPressed('I'))
	{
		light[0].LightPosition.z -= (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('K'))
	{
		light[0].LightPosition.z += (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('J'))
		light[0].LightPosition.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].LightPosition.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].LightPosition.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].LightPosition.y += (float)(LSPEED * dt);

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
	
	if (Application::IsKeyPressed(VK_F3))
	{
		std::cout << Player->getter("position") << "\n";
	}
	static bool pressingpressing = false;
	if (Application::IsKeyPressed('E') && Car->interactionBox->pointInAABB(Player->getter("position")) && pressingpressing == false)
	{
		if (Car->getInVehicle())
		{
			//Player->Position = Player->Position + Car->getRight() * 20;
			Player->getCam()->position.x += Car->getRight().x * 20;
			Player->getCam()->position.z += Car->getRight().z * 20;
			Car->setInVehicle(false);
		}
		else if (!Car->getInVehicle())
			Car->setInVehicle(true);
		pressingpressing = true;
	}
	else if (!Application::IsKeyPressed('E'))
	{
		pressingpressing = false;
	}

	//std::cout << Player->getter("forward") << std::endl;
	//std::cout << Car->hitbox->pointInAABB(Player->getter("position")) << std::endl;
	//std::cout << Car->Position << std::endl;
	//std::cout << Player->Position << std::endl;
	//std::cout << Car->interactionBox->getAABB().pt_Max << std::endl;
	//std::cout << Car->getInVehicle() << std::endl;

	//check collision with objects in land with player
	colManager->CollisionChecker(GalaxyGenerate::get_instance()->system_database[system_id]->land_database[planet_id], Player);
	
	//colManager->CollisionChecker(gen, Player);

	if (Car->getInVehicle())
	{
		Car->Update(dt);
		Player->getCam()->position.x = Car->Position.x;
		Player->getCam()->position.z = Car->Position.z;
		Player->Position = Player->getCam()->position;
	}
	else
	{
		Player->Update(dt, meleeEnemies, rangedEnemies);
	}

	//std::cout << Player->getter("position") << "\n";

	if (isLeavingPlanet)
	{
		if (Application::IsKeyPressed('Y'))
		{
			SceneManager::get_instance()->SceneSelect(2);
		}
		else if (Application::IsKeyPressed('N'))
		{
			isLeavingPlanet = false;
		}
	}

	std::cout << SystemScene::planet << "\n";

	//for (it = meleeEnemies.begin(); it != meleeEnemies.end(); it++)
	//{
	//	(*it)->meleeUpdate(dt, Player);
	//}

	//for (it = rangedEnemies.begin(); it != rangedEnemies.end(); it++)
	//{
	//	(*it)->rangedUpdate(dt, Player);
	//}
	//for (int i = 0; i < meleeEnemies.size(); i++)
	//{
	//	if (meleeEnemies[i]->getHealth() <= 0)
	//	{
	//		meleeEnemies[i]->enemyIsDead = true;
	//		meleeEnemies.erase(meleeEnemies.begin() + i);
	//		i = 0;
	//	}
	//}

	//for (int i = 0; i < rangedEnemies.size(); i++)
	//{
	//	if (rangedEnemies[i]->getHealth() <= 0)
	//	{
	//		rangedEnemies[i]->enemyIsDead = true;
	//		rangedEnemies.erase(rangedEnemies.begin() + i);
	//		i = 0;
	//	}
	//}
}


void PlanetScene::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 MVP;


	viewStack.LoadIdentity();

	
	//viewStack.LookAt(camera.position.x, camera.position.y,		//debug cam
	//camera.position.z, camera.target.x, camera.target.y,
	//camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	if (Car->getInVehicle())
	{
		viewStack.LookAt(Car->Camera->position.x, Car->Camera->position.y,
			Car->Camera->position.z, Car->Camera->target.x, Car->Camera->target.y,
			Car->Camera->target.z, Car->Camera->up.x, Car->Camera->up.y, Car->Camera->up.z);
	}
	else
	{
		viewStack.LookAt(Player->getCam()->position.x, Player->getCam()->position.y,
			Player->getCam()->position.z, Player->getCam()->target.x, Player->getCam()->target.y,
			Player->getCam()->target.z, Player->getCam()->up.x, Player->getCam()->up.y, Player->getCam()->up.z);
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

	//RenderMesh(meshList[GEO_AXES], false);

	RenderSkybox();

	modelStack.PushMatrix();
	modelStack.LoadMatrix(Car->Stamp);
	RenderMesh(meshList[GEO_CAR], true);
	modelStack.PopMatrix();

	//=================================================================================================
	modelStack.PushMatrix();
	modelStack.Translate(light[0].LightPosition.x, light[0].LightPosition.y, light[0].LightPosition.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[1].LightPosition.x, light[1].LightPosition.y, light[1].LightPosition.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();
	//===================================================================================================\

	//for (it = meleeEnemies.begin(); it != meleeEnemies.end(); it++)
	//{
	//	modelStack.PushMatrix();
	//	modelStack.LoadMatrix((*it)->Stamp);
	//	modelStack.Scale(15, 15, 15);
	//	RenderMesh(meshList[GEO_ENEMY], false);
	//	modelStack.PopMatrix();
	//}

	//for (it = rangedEnemies.begin(); it != rangedEnemies.end(); it++)
	//{
	//	modelStack.PushMatrix();
	//	modelStack.LoadMatrix((*it)->Stamp);
	//	modelStack.Scale(15, 15, 15);
	//	RenderMesh(meshList[GEO_ENEMY2], false);
	//	modelStack.PopMatrix();
	//}
	//for (auto &i : Player->bullets)
	//{
	//	modelStack.PushMatrix();
	//	modelStack.LoadMatrix(i->getMatrix());
	//	RenderMesh(meshList[GEO_PLAYERBULLET], false);
	//	modelStack.PopMatrix();
	//}
	//for (it = rangedEnemies.begin(); it != rangedEnemies.end(); it++)
	//{
	//	for (auto &j : (*it)->enemyBullets)
	//	{
	//		modelStack.PushMatrix();
	//		modelStack.LoadMatrix(j->getMatrix());
	//		RenderMesh(meshList[GEO_ENEMYBULLET], false);
	//		modelStack.PopMatrix();
	//	}
	//}

	gen->BuildLand();
	//GalaxyGenerate::get_instance()->system_database[system_id]->land_database[system_id][planet_id]->BuildLand();
	RenderTextOnScreen(meshList[GEO_TEXT], "To Mine ore press [E]", Color(0, 1, 0), 2, 1, 4);
	if (!Application::IsKeyPressed('Q') && !isLeavingPlanet)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "To leave planet press [Q]", Color(1, 0, 0), 2, 1, 2);
	}
	if (Application::IsKeyPressed('Q') && !isLeavingPlanet)
	{
		isLeavingPlanet = true;
		
	}
	if (isLeavingPlanet)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Leave planet ? yes [Y] / no [N]", Color(1, 0, 0), 2, 1, 2);
	}
}

void PlanetScene::RenderMesh(Mesh *mesh, bool enableLight)
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

void PlanetScene::RenderText(Mesh* mesh, std::string text, Color color)
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

void PlanetScene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);

	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
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
void PlanetScene::RenderUI(Mesh* mesh, float x, float y, float sizex, float sizey)
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
//=================================================================================================

void PlanetScene::RenderSkybox()
{
	modelStack.PushMatrix();//push ground
	modelStack.Translate(1230, 0, 1230);

	modelStack.PushMatrix();//seperate from ground
	modelStack.Translate(0, -1100, 0);

	modelStack.PushMatrix();//push top
	modelStack.Translate(0, 2493, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(2502, 1, 2502);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();//end top

	modelStack.PushMatrix();//push back
	modelStack.Translate(0, 1245, 1245);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2500, 1, 2500);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();//end back

	modelStack.PushMatrix();//push front
	modelStack.Translate(0, 1245, -1245);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(2500, 1, 2500);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();//end front

	modelStack.PushMatrix();//push left
	modelStack.Translate(1245, 1245, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(2500, 1, 2500);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();//end left

	modelStack.PushMatrix();//push right
	modelStack.Translate(-1245, 1245, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(2500, 1, 2500);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();//end right

	modelStack.PopMatrix();//end speration

	modelStack.Translate(0, 0, 0);
	modelStack.Scale(2500, 1, 2500);
	RenderMesh(meshList[GEO_BOTTOM], true);
	modelStack.PopMatrix();//end ground
}

void PlanetScene::Exit()
{
	//delete this->gen;
	delete this->Player;
	delete this->colManager;
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}