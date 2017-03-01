
//#include "Application.h"

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SceneManager.h"
#include "StudioProject.h"
#include "PlanetScene.h"
#include "SystemScene.h"
#include "GalaxyScene.h"
#include "StartScene.h"
#include "StationScene.h"
#include "MainMenuScene.h"

#include "GalaxyGenerate.h"
#include "Currency.h"
//static const unsigned char FPS = 60; // FPS of this game
//static const unsigned int frameTime = 1000 / FPS; // time for each frame

GLFWwindow* Application::m_window = NULL;
StopWatch Application::m_timer;
SceneManager * SceneManager::only_instance = 0;

GalaxyGenerate* GalaxyGenerate::instance = 0;
Currency* Currency::instance = 0;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
}

Application::~Application()
{
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); //update opengl the new window size
}
void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(1600, 900, "Computer Graphics", NULL, NULL);
	//m_window = glfwCreateWindow(1600, 900, "Computer Graphics", glfwGetPrimaryMonitor(), NULL);           // making the window full screen

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowSizeCallback(m_window, resize_callback);

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

void Application::Run()
{
	//Main Loop

	createScene();
	SceneManager::get_instance()->getScene()->Init();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		SceneManager::get_instance()->sceneUpdate();
	}						//Check if the ESC key had been pressed or if the window had been closed

	SceneManager::get_instance()->getScene()->Exit();
	delete SceneManager::get_instance()->getScene();
}

void Application::createScene() //adding new scene
{	//id starts with 0
	Scene *startScene = new StartScene();			//0
	Scene *MenuScene = new MainMenuScene();			//1
	Scene *SpaceScene = new StudioProject();		//2
	Scene *LandScene = new PlanetScene();			//3
	Scene *SolarScene = new SystemScene();			//4
	Scene *GalaticScene = new GalaxyScene();		//5
	Scene *stationScene = new StationScene();		//6

	SceneManager::get_instance()->AddScene(startScene);
	SceneManager::get_instance()->AddScene(MenuScene);
	SceneManager::get_instance()->AddScene(SpaceScene);
	SceneManager::get_instance()->AddScene(LandScene);
	SceneManager::get_instance()->AddScene(SolarScene);
	SceneManager::get_instance()->AddScene(GalaticScene);
	SceneManager::get_instance()->AddScene(stationScene);
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
