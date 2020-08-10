#include "GameObjectManager.h"
#include "TextureManager.h"

#include <iostream>

std::vector<GameObject*> GOMA::GameObjects;
std::vector<Tile*> GOMA::CollidableTiles;
std::vector<Obstacle*> GOMA::Obstacles;
std::vector<Tile*> GOMA::BackgroundTiles;

void GameObjectManager::Update()
{
	for (GameObject* obj : GameObjects)
	{
		obj->Update();
	}
	
	CleanEmptyElements();
}

void GameObjectManager::CleanEmptyElements()
{
	for (std::vector<Obstacle*>::iterator obst = Obstacles.begin(); obst != Obstacles.end(); )
	{
		if (not (*obst)->IsActive())
		{
			DeleteFromVectors(*obst);
			obst = Obstacles.erase(obst);
		}
		else
		{
			obst++;
		}
	}
}

void GameObjectManager::DeleteFromVectors(GameObject* delObj)
{
	for (std::vector <GameObject*>::iterator obj = GameObjects.begin(); obj != GameObjects.end(); )
	{
		if (*obj == delObj)
		{
			delete* obj;
			obj = GameObjects.erase(obj);
		}
		else
		{
			obj++;
		}
	}
}

void GameObjectManager::Render()
{
	for (GameObject* GameObject : BackgroundTiles)
		GameObject->Render();
	for (GameObject* GameObject : CollidableTiles)
		GameObject->Render();
	for (GameObject* GameObject : Obstacles)
		GameObject->Render();
}

void GameObjectManager::Clean()
{
	for (std::vector <GameObject*>::iterator obj = GameObjects.begin(); obj != GameObjects.end(); )
	{
		delete* obj;
		obj = GameObjects.erase(obj);
	}
	CollidableTiles.clear();
	CollidableTiles.shrink_to_fit();
	BackgroundTiles.clear();
	BackgroundTiles.shrink_to_fit();
	Obstacles.clear();
	Obstacles.shrink_to_fit();
}

void GameObjectManager::AddBackgroundTile(Tile* obj)
{
	GameObjects.push_back(obj);
	BackgroundTiles.push_back(obj);
}

void GameObjectManager::AddCollidableTile(Tile* obj)
{
	GameObjects.push_back(obj);
	CollidableTiles.push_back(obj);
}

void GameObjectManager::CreateObstacle(ObstacleType type, Vec2 pos)
{
	switch (type)
	{
	case BARREL:
		{
			Barrel* barrel = new Barrel(pos);
			GameObjects.push_back(barrel);
			Obstacles.push_back(barrel);
		}
		break;
	}
}
