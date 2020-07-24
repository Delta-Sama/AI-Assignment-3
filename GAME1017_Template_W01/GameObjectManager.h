#pragma once
#ifndef _GAMEOBJECTMANAGER_H_
#define _GAMEOBJECTMANAGER_H_
#include <SDL_rect.h>
#include <SDL_render.h>
#include <vector>

#include "GameObject.h"

enum MapObjectType
{
	kPlate = 1,
	kSpike,
	kPortal
};

class GameObjectManager
{
public:
	static void Init();
	static void Update();
	static void Render();
	static void Clean();
	
	static std::vector<GameObject*> GameObjectsVec;
private:
	GameObjectManager();
	~GameObjectManager();
};

#endif