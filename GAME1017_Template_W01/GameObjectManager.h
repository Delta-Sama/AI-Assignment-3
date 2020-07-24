#pragma once
#ifndef _GAMEOBJECTMANAGER_H_
#define _GAMEOBJECTMANAGER_H_

#include <SDL_rect.h>
#include <SDL_render.h>
#include <vector>

#include "GameObject.h"
#include "Tile.h"

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
	static void AddCollidableTile(Tile* obj);

	static std::vector<GameObject*>* GetObjects() { return &GameObjectsVec; }
	static std::vector<Tile*>* GetCollidableTiles() { return &CollidableTilesVec; }
private:
	GameObjectManager();
	~GameObjectManager();

	static std::vector<GameObject*> GameObjectsVec;
	static std::vector<Tile*> CollidableTilesVec;
};

#endif