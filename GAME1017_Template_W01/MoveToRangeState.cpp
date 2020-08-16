#include "MoveToRangeState.h"


#include "CollisionManager.h"
#include "EnemyManager.h"
#include "Util.h"

MoveToRangeState::MoveToRangeState(Enemy* enemy) : BehaviorState(enemy)
{}

MoveToRangeState::~MoveToRangeState() = default;

void MoveToRangeState::Enter()
{
	m_entity->SetStatus(MOVETOLOS);
	m_update_frame = m_max_update_frame;
}

void MoveToRangeState::ClearPath()
{
	if (!m_path.empty())
	{
		m_path.clear();
	}
}

void MoveToRangeState::Update()
{
	// If its time to update:
	m_update_frame++;

	SDL_FPoint player_center = ENMA::GetPlayer()->GetCenter();
	long plr_ent_dist = (long int)MAMA::SquareDistance(&m_entity->GetCenter(), &player_center);
	bool tunnel_LOS = COMA::TunnelLOSCheck(&m_entity->GetCenter(), &player_center, TUNNEL_ENTITY_WIDTH);
	
	if (not tunnel_LOS)
	{
		if (m_update_frame > m_max_update_frame)
		{
			m_update_frame = 0;
			// Find nearest to the entity LOS node:
			PathNode* LOS_node = COMA::GetClosestToPointNode(m_entity->GetCenter(), true,true,{MELEE_DIST * 4, 9999});

			// Save path:
			if (LOS_node and m_entity->GetShortestLOSNode())
			{
				//Util::QueueCircle({ LOS_node->x, LOS_node->y }, 20, { 1,0,0,1 });
				ClearPath();
				m_path = PAMA::GetShortestPath(m_entity->GetShortestLOSNode(), LOS_node, true);
			}
		}
	}
	else
	{			
		if (plr_ent_dist > pow(RANGE_DISTANCE,2))
		{
			ClearPath();
			m_entity->Seek(player_center);
		}
		else if (plr_ent_dist < pow(AVOID_DISTANCE,2))
		{
			if (m_update_frame > m_max_update_frame)
			{
				m_update_frame = 0;
				PathNode* LOS_node = nullptr;
				long min_dist = 99999;
				for (PathNode* node : *PAMA::GetNodes())
				{
					if (node->GetPlayerLOS())
					{
						SDL_FPoint temp_pos = { node->x, node->y };
						long plr_node_dist = (long int)MAMA::SquareDistance(&player_center, &temp_pos);
						long ent_node_dist = (long int)MAMA::SquareDistance(&m_entity->GetCenter(), &temp_pos);
						
						if (plr_node_dist > pow(RANGE_DISTANCE,2) and ent_node_dist < min_dist)
						{
							min_dist = ent_node_dist;
							LOS_node = node;
						}
					}
				}
				if (LOS_node and m_entity->GetShortestLOSNode())
				{
					ClearPath();
					m_path = PAMA::GetShortestPath(m_entity->GetShortestLOSNode(), LOS_node, true);
				}
			}
		}
	}

	if (not m_path.empty())
	{
		m_entity->FollowThePath(m_path);
	}
}

void MoveToRangeState::Transition()
{
	SDL_FPoint player_center = ENMA::GetPlayer()->GetCenter();
	long plr_ent_dist = (long int)MAMA::SquareDistance(&m_entity->GetCenter(), &player_center);
	bool tunnel_LOS = COMA::TunnelLOSCheck(&m_entity->GetCenter(), &player_center, TUNNEL_ENTITY_WIDTH);

	if (plr_ent_dist < pow(RANGE_DISTANCE, 2) and plr_ent_dist > pow(AVOID_DISTANCE, 2))
	{
		m_entity->GetAIState()->PushState(RANGEATTACK);
		return;
	}

	if (m_entity->GetHealth() < m_entity->GetMaxHealth() * 0.25)
	{
		m_entity->GetAIState()->ChangeState(FLEE);
		return;
	}

	if (m_entity->Hitted() and m_entity->GetHideTime() < Engine::Instance().GetFrames() + HIDE_COOLDOWN)
	{
		m_entity->GetAIState()->ChangeState(MOVETOCOVER);
		return;
	}
}

void MoveToRangeState::Exit()
{
	
}
