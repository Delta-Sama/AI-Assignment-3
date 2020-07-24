#include "GameObjectManager.h"
#include "TextureManager.h"

#include <iostream>

std::vector<GameObject*> GameObjectManager::GameObjectsVec;

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{

}

void GameObjectManager::Init()
{
	//TextureManager::RegisterTexture("Img/brick.png", "plate");
	
}
void GameObjectManager::Update()
{
	for (GameObject* obj : GameObjectsVec)
	{
		obj->update();
	}
}


void GameObjectManager::Render()
{
	for (GameObject* GameObject : GameObjectsVec)
	{
		GameObject->Render();
	}
}

void GameObjectManager::Clean()
{
	for (std::vector <GameObject*>::iterator obj = GameObjectsVec.begin(); obj != GameObjectsVec.end(); )
	{
		delete* obj;
		obj = GameObjectsVec.erase(obj);
		++obj;
	}
}

void GameObjectManager::AddObject(GameObject* obj)
{
	GameObjectsVec.push_back(obj);
}