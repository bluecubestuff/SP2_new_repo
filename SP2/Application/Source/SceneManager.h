#ifndef _SCENE_MANAGER_
#define _SCENE_MANAGER_

#include "Scene.h"
#include "Application.h"
#include "DetectMemoryLeak.h"

#include <map>
using std::map;

class SceneManager
{
public:

	~SceneManager();						//desctructor

	Scene* getScene();
	void AddScene(Scene*);					//add new scene to database
	void SetNextScene();					//set the next scene
	void sceneUpdate();						//update scene
	void SetPrevScene();
	void TimedScene(float);					//for the start screen
	void SceneSelect(unsigned);

	static SceneManager *get_instance()		//singleton to get only one instance of obj
	{
		if (!only_instance)
		{
			only_instance = new SceneManager; 
		}
		return only_instance;
	}

private:
	SceneManager();							 //constructor

	static SceneManager* only_instance;		
	map <unsigned, Scene*> sceneStorage;	//database for scene
	int currSceneID, nextSceneID;			//to iterate through the different scene
	bool isTime = false;					//check if time is up for startscreen;
};

#endif