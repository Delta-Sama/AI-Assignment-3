#include "Debug.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "PathManager.h"
#include "Util.h"

DebugMode::DebugMode(GameState* scene)
{
	m_playScene = scene;
}

void DebugMode::Draw()
{
	if (m_mode)
	{
		Player* player = m_playScene->GetPlayer();
		SDL_FPoint playerCenter = player->GetCenter();

		Vec4 color = { 0, 1, 0, 1 };
		
		for (Enemy* enemy : *ENMA::GetEnemies())
		{
			if (enemy->GetPlayerLOS())
				Util::DrawLine(playerCenter, enemy->GetCenter());
			else
				Util::DrawLine(playerCenter, enemy->GetCenter(), Vec4(1, 0, 0, 1));

			Vec4 n_color = Vec4{ 0, 1, 0, 1 };
			if (CollisionManager::AABBCheck(*player->GetDstP(), *enemy->GetDstP()))
			{
				n_color = Vec4{ 1, 0, 0, 1 };
				color = Vec4{ 1, 0, 0, 1 };
			}
			
			Util::DrawRect({ enemy->GetDstP()->x, enemy->GetDstP()->y }, enemy->GetDstP()->w, enemy->GetDstP()->h, n_color);
		}
		Util::DrawRect({ player->GetDstP()->x, player->GetDstP()->y }, player->GetDstP()->w, player->GetDstP()->h, color);

		for (PathNode* node : *PAMA::GetNodes())
		{
			Vec4 nodeColor = { 0.3,0.3,1,1 };
			if (!node->GetPlayerLOS())
				nodeColor = Vec4(1, 0, 0, 1);
			Util::DrawCircle({ (float)node->x, (float)node->y }, 5, nodeColor);

			/*for (PathConnection* connection : node->GetConnections())
			{
				SDL_FPoint from = {(float)connection->GetFromNode()->x, (float)connection->GetFromNode()->y};
				SDL_FPoint to = { (float)connection->GetToNode()->x, (float)connection->GetToNode()->y };
				Util::DrawLine(from, to, {1,1,0,1});
			*/
		}

		for (Enemy* enemy : *ENMA::GetEnemies())
		{
			if (enemy->GetGoal())
			{
				SDL_FPoint to = { enemy->GetGoal()->x, enemy->GetGoal()->y };
				Util::DrawLine(enemy->GetCenter(), to, { 1,1,0,1 });
			}
		}
	}
}