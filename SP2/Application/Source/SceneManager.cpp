#include "SceneManager.h"
#include <iostream>
SceneManager::SceneManager() : currSceneID(0), nextSceneID(0) {}	//constructor

SceneManager::~SceneManager()										//destructor	
{
	delete only_instance;
}									

void SceneManager::AddScene(Scene* newScene)						//AddScene
{
	if (nextSceneID > 0)	//check if is not 1st scene
	{
		//nextSceneID++;
		sceneStorage[nextSceneID] = newScene;
	}
	else					//1st scene
	{
		sceneStorage[currSceneID] = newScene;	//assign it to map
	}
	nextSceneID++;							//move next ID forward
}

void SceneManager::SetNextScene()
{
	currSceneID += 1;
	if (currSceneID > sceneStorage.size())
	{
		currSceneID -= 1;
	}
	//nextSceneID++;
}

void SceneManager::SetPrevScene()
{
	if (currSceneID > 0 && currSceneID != 0)
	{
		currSceneID -= 1;
	}
}

void SceneManager::sceneUpdate()
{
	if (Application::IsKeyPressed(VK_F1) && currSceneID < sceneStorage.size() - 1 || isTime) //place holder
	{
		isTime = false;
		sceneStorage[currSceneID]->Exit(); //exit prev scene
		SetNextScene();					   //set next scene
		sceneStorage[currSceneID]->Init(); //init next scene
	}
	else if (Application::IsKeyPressed(VK_F2) && currSceneID > 0 && currSceneID != 0)
	{
		sceneStorage[currSceneID]->Exit(); //exit prev scene
		SetPrevScene();		   //set next scene
		sceneStorage[currSceneID]->Init(); //init next scene
	}

	//std::cout<<sceneStorage.size();

	sceneStorage[currSceneID]->Update(Application::m_timer.getElapsedTime());
	sceneStorage[currSceneID]->Render();
	//Swap buffers
	glfwSwapBuffers(Application::m_window);
	//Get and organize events, like keyboard and mouse input, window resizing, etc...
	glfwPollEvents();
	Application::m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   		 
}

Scene* SceneManager::getScene()
{
	return sceneStorage[currSceneID];
}

void SceneManager::TimedScene(float timer)
{
	if (timer > 3)
	{
		isTime = true;
	}
}