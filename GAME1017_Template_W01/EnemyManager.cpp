#include "EnemyManager.h"

#include "CollisionManager.h"
#include "RedSniper.h"

std::vector<Enemy*> ENMA::EnemiesVec;
GameState* ENMA::m_scene;
int ENMA::m_diedEnemies = 0;

void EnemyManager::Update()
{
	for (std::vector<Enemy*>::iterator enemy = EnemiesVec.begin(); enemy != EnemiesVec.end();)
	{
		if (!(*enemy)->GetActive())
		{
			m_diedEnemies++;
			enemy = EnemiesVec.erase(enemy);
		}
		else
		{
			(*enemy)->update();
			enemy++;
		}
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
