#include "Debug.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
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
		for (Enemy* enemy : *ENMA::GetEnemies())
		{
			if (CollisionManager::LOSCheck(player, enemy))
				Util::DrawLine(playerCenter, enemy->GetCenter());
			else
				Util::DrawLine(playerCenter, enemy->GetCenter(), Vec4(1, 0, 0, 1));


			Vec4 color = (CollisionManager::AABBCheck(*player->GetDstP(), *enemy->GetDstP())
				? Vec4{ 1, 0, 0, 1 } : Vec4{ 0, 1, 0, 1 });
			Util::DrawRect({ player->GetDstP()->x, player->GetDstP()->y }, player->GetDstP()->w, player->GetDstP()->h, color);

			Util::DrawRect({ enemy->GetDstP()->x, enemy->GetDstP()->y }, enemy->GetDstP()->w, enemy->GetDstP()->h, color);
		}
	}
}