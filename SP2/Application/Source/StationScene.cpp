#include "StationScene.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "SceneManager.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "Weapon.h"

//#include "LandGenerate.h"
#include <iostream>

StationScene::StationScene()
{
	//Player = new LandPlayer(Vector3(0, 5, 0), Vector3(0, 0, 1), Vector3(1, 0, 0), 100.f);
	camera = new StationCamera;

	mainGate = new Func_AABB(Vector3(-20, 0, -60), Vector3(20, 10, -40));
	//station = new Func_AABB(Vector3(0, 30, -60), Vector3(100, 30, 340));
}

StationScene::~StationScene()
{
}

void StationScene::Init()
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
	//================================================================================================
	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");
	//================================================================================================
	//================================================================================================
	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");
	//================================================================================================
	//================================================================================================
	m_parameters[U_LIGHT4_POSITION] = glGetUniformLocation(m_programID, "lights[4].position_cameraspace");
	m_parameters[U_LIGHT4_COLOR] = glGetUniformLocation(m_programID, "lights[4].color");
	m_parameters[U_LIGHT4_POWER] = glGetUniformLocation(m_programID, "lights[4].power");
	m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID, "lights[4].kC");
	m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID, "lights[4].kL");
	m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID, "lights[4].kQ");
	m_parameters[U_LIGHT4_TYPE] = glGetUniformLocation(m_programID, "lights[4].type");
	m_parameters[U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[4].spotDirection");
	m_parameters[U_LIGHT4_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[4].cosCutoff");
	m_parameters[U_LIGHT4_COSINNER] = glGetUniformLocation(m_programID, "lights[4].cosInner");
	m_parameters[U_LIGHT4_EXPONENT] = glGetUniformLocation(m_programID, "lights[4].exponent");
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
	//Player = new LandPlayer(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(1, 0, 0), 100.f);
	//=============================================================================

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 24, 13, 1);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 24, 13, 1);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//bkg2_back.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//bkg2_front.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//bkg2_left.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//bkg2_right.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bkg2_bot.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//bkg2_top.tga");

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("Cube", Color(0.6f, 0.4f, 0.3f));

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_GREENPLANET] = MeshBuilder::GenerateOBJ("greenPlanet", "OBJ//Sphere2.OBJ");
	meshList[GEO_GREENPLANET]->textureID = LoadTGA("Image//GreenPlanet.tga");

	meshList[GEO_DESERTPLANET] = MeshBuilder::GenerateOBJ("desertPlanet", "OBJ//Sphere2.OBJ");
	meshList[GEO_DESERTPLANET]->textureID = LoadTGA("Image//DesertPlanet.tga");

	meshList[GEO_BLUEPLANET] = MeshBuilder::GenerateOBJ("bluePlanet", "OBJ//Sphere2.OBJ");
	meshList[GEO_BLUEPLANET]->textureID = LoadTGA("Image//BluePlanet.tga");

	meshList[GEO_CRAFT] = MeshBuilder::GenerateOBJ("greenPlanet", "OBJ//feedback.OBJ");
	meshList[GEO_CRAFT]->textureID = LoadTGA("Image//craftingMenu.tga");

	meshList[GEO_SELL] = MeshBuilder::GenerateOBJ("greenPlanet", "OBJ//feedback.OBJ");
	meshList[GEO_SELL]->textureID = LoadTGA("Image//sellingMenu.tga");
	
	meshList[GEO_WAYPOINT] = MeshBuilder::GenerateOBJ("greenPlanet", "OBJ//WaypointMarker.OBJ");
	meshList[GEO_WAYPOINT]->textureID = LoadTGA("Image//waypoint.tga");

	meshList[GEO_SPACE_STATION] = MeshBuilder::GenerateOBJ("space station interior", "OBJ//StationInterior.OBJ");
	meshList[GEO_SPACE_STATION]->textureID = LoadTGA("Image//spacestationinterior.tga");
	//------------------------------------------------------------------------------------------
	//light
	light[0].type = Light::LIGHT_POINT;
	light[0].LightPosition.Set(0, 50, 150);
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
	light[1].LightPosition.Set(0, 50, 0);
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

	//=============================================================================
	//light
	light[2].type = Light::LIGHT_POINT;
	light[2].LightPosition.Set(0, 50, 300);
	light[2].color.Set(1, 1, 1);
	light[2].power = 2;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 2, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);
	//=============================================================================

	//=============================================================================
	//light
	light[3].type = Light::LIGHT_POINT;
	light[3].LightPosition.Set(70, 50, 150);
	light[3].color.Set(1, 1, 1);
	light[3].power = 1;
	light[3].kC = 1.f;
	light[3].kL = 0.01f;
	light[3].kQ = 0.001f;
	light[3].cosCutoff = cos(Math::DegreeToRadian(45));
	light[3].cosInner = cos(Math::DegreeToRadian(30));
	light[3].exponent = 3.f;
	light[3].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT3_TYPE], light[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], light[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], light[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], light[3].exponent);
	//=============================================================================

	//=============================================================================
	//light
	light[4].type = Light::LIGHT_POINT;
	light[4].LightPosition.Set(-70, 50, 150);
	light[4].color.Set(1, 1, 1);
	light[4].power = 1;
	light[4].kC = 1.f;
	light[4].kL = 0.01f;
	light[4].kQ = 0.001f;
	light[4].cosCutoff = cos(Math::DegreeToRadian(45));
	light[4].cosInner = cos(Math::DegreeToRadian(30));
	light[4].exponent = 3.f;
	light[4].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT4_TYPE], light[4].type);
	glUniform3fv(m_parameters[U_LIGHT4_COLOR], 1, &light[4].color.r);
	glUniform1f(m_parameters[U_LIGHT4_POWER], light[4].power);
	glUniform1f(m_parameters[U_LIGHT4_KC], light[4].kC);
	glUniform1f(m_parameters[U_LIGHT4_KL], light[4].kL);
	glUniform1f(m_parameters[U_LIGHT4_KQ], light[4].kQ);
	glUniform1f(m_parameters[U_LIGHT4_COSCUTOFF], light[4].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT4_COSINNER], light[4].cosInner);
	glUniform1f(m_parameters[U_LIGHT4_EXPONENT], light[4].exponent);
	//=============================================================================


	glUniform1i(m_parameters[U_NUMLIGHTS], 6);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 100000.f);
	projectionStack.LoadMatrix(projection);
	srand((unsigned)(time(NULL)));

	ShowCursor(false);

	camera->Init(Vector3(0, 5, 0), Vector3(0, 5, 1), Vector3(0, 1, 0));
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void StationScene::Update(double dt)
{
	float LSPEED = 10.f;
	//meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", Player->getter("right"), Player->getter("up"), Player->getter("forward"));

	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	//light_controls---------------------------------------------------------------
	if (Application::IsKeyPressed('I'))
	{
		light[1].LightPosition.z -= (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('K'))
	{
		light[1].LightPosition.z += (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('J'))
		light[1].LightPosition.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[1].LightPosition.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[1].LightPosition.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[1].LightPosition.y += (float)(LSPEED * dt);

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
	camera->Update(dt);
	pos = std::to_string(camera->position.x) + " : " + std::to_string(camera->position.y) + " : " + std::to_string(camera->position.z);
	if (mainGate->pointInAABB(camera->position))
	{
		SceneManager::get_instance()->SceneSelect(2);
	}

	ironQ = to_string(Currency::get_instance()->get_mineral("iron"));
	titaniumQ = to_string(Currency::get_instance()->get_mineral("titanium"));
	mithrilQ = to_string(Currency::get_instance()->get_mineral("mithril"));
	bismuthQ = to_string(Currency::get_instance()->get_mineral("bismuth"));

	cred = to_string(Currency::get_instance()->value_getter());

	hull = to_string((int)StudioProject::Player->getHP());
	shield = to_string((int)StudioProject::Player->getFullSP());
	thrust = to_string((int)StudioProject::Player->getThrust());

	hPrice = to_string(NPC::hPrice);
	sPrice = to_string(NPC::sPrice);
	tPrice = to_string(NPC::tPrice);

	//StudioProject::Player->shieldUpdate(dt);
	//std::cout << Currency::get_instance()->get_mineral("iron") << ", credits: " << Currency::get_instance()->value_getter() << std::endl;
}

void StationScene::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 MVP;


	viewStack.LoadIdentity();


	//viewStack.LookAt(camera.position.x, camera.position.y,		//debug cam
	//camera.position.z, camera.target.x, camera.target.y,
	//camera.target.z, camera.up.x, camera.up.y, camera.up.z);

	viewStack.LookAt(camera->position.x, camera->position.y,
		camera->position.z, camera->target.x, camera->target.y,
		camera->target.z, camera->up.x, camera->up.y, camera->up.z);


	Position lightPosition_cameraspace = viewStack.Top() * light[0].LightPosition;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	//===================================================================================
	Position lightPosition_cameraspace2 = viewStack.Top() * light[1].LightPosition;//test
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace2.x);//test
	//===================================================================================
	Position lightPosition_cameraspace3 = viewStack.Top() * light[2].LightPosition;//test
	glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace3.x);//test
	//===================================================================================
	Position lightPosition_cameraspace4 = viewStack.Top() * light[3].LightPosition;//test
	glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace4.x);//test
	//===================================================================================
	Position lightPosition_cameraspace5 = viewStack.Top() * light[4].LightPosition;//test
	glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace5.x);//test
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

	for (int i = 0; i < 6; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(light[i].LightPosition.x, light[i].LightPosition.y, light[i].LightPosition.z);
		RenderMesh(meshList[GEO_LIGHTBALL], false);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Scale(20, 20, 20);
	modelStack.Translate(0, 0, 7);
	RenderMesh(meshList[GEO_SPACE_STATION], true);
	modelStack.PopMatrix();

	if (camera->craft)
	{
		RenderUI(meshList[GEO_CRAFT], 800, 450, 1600, 900);
		RenderTextOnScreen(meshList[GEO_TEXT], hull, Color(1, 1, 1), 100, 900, 750);
		RenderTextOnScreen(meshList[GEO_TEXT], shield, Color(1, 1, 1), 100, 900, 450);
		RenderTextOnScreen(meshList[GEO_TEXT], thrust, Color(1, 1, 1), 100, 900, 150);
		RenderTextOnScreen(meshList[GEO_TEXT], cred, Color(1, 1, 0), 50, 1450, 870);
		RenderTextOnScreen(meshList[GEO_TEXT], "-" + hPrice, Color(1, 1, 1), 75, 1450, 750);
		RenderTextOnScreen(meshList[GEO_TEXT], "-" + sPrice, Color(1, 1, 1), 75, 1450, 450);
		RenderTextOnScreen(meshList[GEO_TEXT], "-" + tPrice, Color(1, 1, 1), 75, 1450, 150);
		RenderUI(meshList[GEO_WAYPOINT], camera->mPos.x, camera->mPos.y, 20, 20);
	}
	if (camera->sell)
	{
		RenderUI(meshList[GEO_SELL], 800, 450, 1600, 900);
		RenderTextOnScreen(meshList[GEO_TEXT], ironQ, Color(1, 1, 1), 80, 600, 300);
		RenderTextOnScreen(meshList[GEO_TEXT], titaniumQ, Color(1, 1, 1), 80, 600, 215);
		RenderTextOnScreen(meshList[GEO_TEXT], mithrilQ, Color(1, 1, 1), 80, 600, 130);
		RenderTextOnScreen(meshList[GEO_TEXT], bismuthQ, Color(1, 1, 1), 80, 600, 45);
		RenderTextOnScreen(meshList[GEO_TEXT], cred, Color(1, 1, 1), 80, 1000, 390);
		RenderUI(meshList[GEO_WAYPOINT], camera->mPos.x, camera->mPos.y, 20, 20);
	}
	/*modelStack.PushMatrix();
	modelStack.Translate(camera->position.x, 0, camera->position.z);
	modelStack.Scale(0.1, 0.1, 0.1);
	RenderMesh(meshList[GEO_SPHERE], false);
	modelStack.PopMatrix();*/

	//RenderTextOnScreen(meshList[GEO_TEXT], pos, Color(1, 0, 0), 30, 30, 894);
}

void StationScene::RenderMesh(Mesh *mesh, bool enableLight)
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

void StationScene::RenderText(Mesh* mesh, std::string text, Color color)
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

void StationScene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);

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
void StationScene::RenderUI(Mesh* mesh, float x, float y, float sizex, float sizey)
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

void StationScene::RenderSkybox()
{
	modelStack.PushMatrix();//push ground
	modelStack.Translate(950, 0, 950);
	modelStack.Scale(10, 10, 10);

	modelStack.PushMatrix();//seperate from ground

	modelStack.PushMatrix();//push top
	modelStack.Translate(0, 1995, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(-90, 0, 1, 0);
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

	//modelStack.Translate(0, 0, 0);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(2000, 1, 2000);
	//RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();//end ground
}

void StationScene::Exit()
{
	//delete Player;
	delete camera;
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}