#pragma once
#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <map>
#include "Tile.h"

class GameState;

class Level
{
public:
	Level(GameState* scene) : m_scene(scene) {};
	~Level() {};

	virtual void Load() = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;

	std::vector<PathNode*>* GetPatrolPath() { return &m_patrolPath; }

private:

protected:
	std::map<char, Tile*> m_tiles;
	std::vector<PathNode*> m_patrolPath;
	GameState* m_scene;
};

#include "States.h"

#endif