#pragma once
#ifndef _GAMEOBJECTMANAGER_H_
#define _GAMEOBJECTMANAGER_H_

#include <SDL_rect.h>
#include <SDL_render.h>
#include <vector>

#include "GameObject.h"
#include "Obstacle.h"
#include "Tile.h"

class GameObjectManager
{
public:
	static void Update();
	static void Render();
	static void Clean();
	
	static void AddBackgroundTile(Tile* obj);
	static void AddCollidableTile(Tile* obj);
	
	static void CreateObstacle(ObstacleType type, Vec2 pos);

	static void CleanEmptyElements();
	static void DeleteFromVectors(GameObject* delObj);

	static std::vector<GameObject*>* GetObjects() { return &GameObjects; }
	static std::vector<Tile*>* GetCollidableTiles() { return &CollidableTiles; }
	static std::vector<Obstacle*>* GetObstacles() { return &Obstacles; }
	
private:

	static std::vector<GameObject*> GameObjects;
	static std::vector<Tile*> CollidableTiles;
	static std::vector<Tile*> BackgroundTiles;
	static std::vector<Obstacle*> Obstacles;
};

typedef GameObjectManager GOMA;

#endif