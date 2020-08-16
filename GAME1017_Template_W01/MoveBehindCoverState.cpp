#include "MoveBehindCoverState.h"

MoveBehindCoverState::MoveBehindCoverState(Enemy* enemy) : BehaviorState(enemy)
{
}

MoveBehindCoverState::~MoveBehindCoverState() = default;

void MoveBehindCoverState::Enter()
{
	m_entity->SetStatus(MOVETOCOVER);
	m_update_frame = m_max_update_frame;
}

void MoveBehindCoverState::Update()
{
	// If its time to update:
	if (++m_update_frame > m_max_update_frame)
	{
		m_update_frame = 0;

		// Find nearest LOS node:
		PathNode* LOS_node = nullptr;
		long min_dist = 99999;

		for (PathNode* node : *PAMA::GetNodes())
		{
			if (not node->GetPlayerLOS())
			{
				SDL_FPoint temp_pos = { node->x, node->y };
				long dist = (long int)MAMA::SquareDistance(&m_entity->GetCenter(), &temp_pos);

				if (dist < min_dist)
				{

					min_dist = dist;
					LOS_node = node;
				}
			}
		}
		// Save the path:
		if (LOS_node and m_entity->GetShortestLOSNode())
		{
			if (!m_path.empty())
			{
				m_path.clear();
			}
			m_path = PAMA::GetShortestPath(m_entity->GetShortestLOSNode(), LOS_node);
		}
	}
	else
	{
		m_entity->FollowThePath(m_path);
	}
}

void MoveBehindCoverState::Transition()
{
	if (m_path.empty())
	{
		m_entity->GetAIState()->ChangeState(WAITBEHINDCOVER);
		return;
	}
	m_entity->IncrementCoveringTime();
	if (m_entity->GetCoveringTime() > MAX_COVER_TIME)
	{
		m_entity->SetCoveringTime(0);
		m_entity->GetAIState()->ChangeState(MOVETOLOS);
		return;
	}
}

void MoveBehindCoverState::Exit()
{

}