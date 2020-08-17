#include "MoveToLOSState.h"

#include "CollisionManager.h"
#include "EnemyManager.h"

MoveToLOSState::MoveToLOSState(Enemy* enemy) : BehaviorState(enemy), m_update_frame(0)
{
}

MoveToLOSState::~MoveToLOSState() = default;

void MoveToLOSState::Enter()
{
	m_entity->SetStatus(MOVETOLOS);
	m_update_frame = m_max_update_frame;
}

void MoveToLOSState::Update()
{
	// If its time to update:
	if (++m_update_frame > m_max_update_frame)
	{
		m_update_frame = 0;

		// Find nearest to the player LOS node:
		PathNode* LOS_node = nullptr;
		long min_dist = 99999;

		for (PathNode* node : *PAMA::GetNodes())
		{
			if (node->GetPlayerLOS())
			{
				SDL_FPoint temp_pos = { node->x, node->y };
				long dist = (long int)MAMA::SquareDistance(&ENMA::GetPlayer()->GetCenter(), &temp_pos);

				if (dist < min_dist)
				{

					min_dist = dist;
					LOS_node = node;
				}
			}
		}
		// Save path:
		if (LOS_node and m_entity->GetShortestLOSNode())
		{
			if (!m_path.empty())
			{
				m_path.clear();
			}
			m_path = PAMA::GetShortestPath(m_entity->GetShortestLOSNode(), LOS_node, true);
		}
	}
	else
	{
		m_entity->FollowThePath(m_path);
	}

	// Draw the path
	/*for (int i = 0; i < m_path.size(); i++)
	{
		PathNode* from = m_path[i]->GetFromNode();
		PathNode* to = m_path[i]->GetToNode();
		Util::QueueLine({ from->x, from->y }, { to->x, to->y }, { 255,0,0,255 });
	}*/
}

void MoveToLOSState::Transition()
{
	if (m_path.empty() and m_entity->GetPlayerDetectRad())
	{
		if (m_entity->GetEnemyType() == MELEETYPE)
			m_entity->GetAIState()->ChangeState(MOVETOPLAYER);
		else if (m_entity->GetEnemyType() == RANGETYPE)
			m_entity->GetAIState()->ChangeState(MOVETORANGE);
		
		return;
	}

	if (m_entity->GetHealth() < m_entity->GetMaxHealth() * 0.25)
	{
		m_entity->GetAIState()->ChangeState(FLEE);
		return;
	}
}

void MoveToLOSState::Exit()
{

}