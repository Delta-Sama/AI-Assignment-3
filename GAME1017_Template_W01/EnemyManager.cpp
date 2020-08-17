#include "EnemyManager.h"

#include "BrownCutter.h"
#include "CollisionManager.h"
#include "RedSniper.h"

std::vector<Enemy*> ENMA::EnemiesVec;
std::vector<Enemy*> ENMA::LateEnemiesVec;
GameState* ENMA::m_scene;
int ENMA::m_diedEnemies = 0;
Player* ENMA::m_player = nullptr;

void EnemyManager::Update()
{
	for (std::vector<Enemy*>::iterator enemy = EnemiesVec.begin(); enemy != EnemiesVec.end();)
	{
		if (!(*enemy)->GetActive())
		{
			if ((*enemy)->GetStatus() != LEAVING)
			{
				m_diedEnemies++;
			}
			delete *enemy;
			enemy = EnemiesVec.erase(enemy);
		}
		else
		{
			(*enemy)->Update();
			enemy++;
		}
	}

	for (Enemy* enemy : LateEnemiesVec)
	{
		EnemiesVec.push_back(enemy);
	}
	LateEnemiesVec.clear();
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
		if (enemy->GetCollidable())
		{
			COMA::CheckMapCollision(enemy);
		}
	}
}

void EnemyManager::Clean()
{
	for (Enemy* enemy : EnemiesVec)
	{
		enemy->Clean();
		delete enemy;
	}

	EnemiesVec.clear();
	EnemiesVec.shrink_to_fit();
}

void EnemyManager::LateAddEnemy(EnemyType type, Vec2 pos, int angle)
{
	Enemy* enemy;

	switch (type)
	{
	case RANGETYPE:
		enemy = new RedSniper(pos);
		break;
	case MELEETYPE:
		enemy = new BrownCutter(pos);
		break;
	default:
		return;
	}

	if (angle != 0)
		enemy->SetAngle(angle);

	LateEnemiesVec.push_back(enemy);
}

void EnemyManager::AddEnemy(EnemyType type, Vec2 pos, int angle)
{
	Enemy* enemy;

	switch (type)
	{
	case RANGETYPE:
		enemy = new RedSniper(pos);
		break;
	case MELEETYPE:
		enemy = new BrownCutter(pos);
		break;
	default:
		return;
	}

	if (angle != 0)
		enemy->SetAngle(angle);
	
	EnemiesVec.push_back(enemy);
}
