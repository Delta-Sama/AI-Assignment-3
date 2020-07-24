#include "EnemyManager.h"

#include "CollisionManager.h"
#include "RedSniper.h"

std::vector<Enemy*> ENMA::EnemiesVec;
GameState* ENMA::m_scene;

void EnemyManager::Update()
{
	for (Enemy* enemy : EnemiesVec)
	{
		enemy->update();
	}
}

void EnemyManager::Render()
{
	for (Enemy* enemy : EnemiesVec)
	{
		enemy->Render();
	}
}

void EnemyManager::CheckCollision()
{
	for (Enemy* enemy : EnemiesVec)
	{
		COMA::CheckMapCollision(enemy);
	}
}

void EnemyManager::Clean()
{
	for (Enemy* enemy : EnemiesVec)
	{
		enemy->clean();
		delete enemy;
	}

	EnemiesVec.clear();
	EnemiesVec.shrink_to_fit();
}

void EnemyManager::AddEnemy(EnemyType type, Vec2 pos)
{
	Enemy* enemy;

	switch (type)
	{
	case REDSNIPER:
		enemy = new RedSniper(pos);
		break;
	default:
		return;
	}
	
	EnemiesVec.push_back(enemy);
}
