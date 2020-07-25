#pragma once
#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

#include "Enemy.h"

#include <vector>

enum EnemyType { REDSNIPER };

class EnemyManager
{
public:
	static void Update();
	static void Render();
	static void CheckCollision();
	static void Clean();
	
	static void AddEnemy(EnemyType type, Vec2 pos);
	
	static std::vector<Enemy*>* GetEnemies() { return &EnemiesVec; }
	static int GetKilledEnemies() { return m_diedEnemies; }
	static GameState* GetScene() { return m_scene; }
	
	static void SetScene(GameState* scene) { m_scene = scene; };
	
private:
	static std::vector<Enemy*> EnemiesVec;
	static GameState* m_scene;
	static int m_diedEnemies;
	
	EnemyManager() {}
};

typedef EnemyManager ENMA;

#endif