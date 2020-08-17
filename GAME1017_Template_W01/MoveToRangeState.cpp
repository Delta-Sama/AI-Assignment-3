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

			if (LOS_node == nullptr)
				LOS_node = COMA::GetClosestToPointNode(m_entity->GetCenter(), true, true);
			
			// Save path:
			if (LOS_node and m_entity->GetShortestLOSNode())
			{
				//Util::QueueCircle({ LOS_node->x, LOS_node->y }, 20, { 1,0,0,1 });
				ClearPath();
				m_path = PAMA::GetShortestPath(m_entity->GetShortestLOSNode(), LOS_node, true);
			}
			else
			{
				m_entity->GetAIState()->ChangeState(PATROL);
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
		else if (plr_ent_dist < pow(AVOID_DISTANCE, 2))
		{
			m_entity->Flee();
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
	bool tunnel_LOS = COMA::TunnelLOSCheck(&m_entity->GetCenter(), &player_center, 8);

	if (tunnel_LOS and plr_ent_dist < pow(RANGE_DISTANCE, 2) and plr_ent_dist > pow(AVOID_DISTANCE, 2))
	{
		if (not m_entity->IsMoving())
		{
			float angle = MAMA::AngleBetweenPoints((ENMA::GetPlayer()->GetCenter().y - m_entity->GetCenter().y), (ENMA::GetPlayer()->GetCenter().x - m_entity->GetCenter().x));
			m_entity->SetSmoothAngle(angle);
		}
		
		float start_angle = MAMA::Rad2Deg(MAMA::AngleBetweenPoints(player_center.y - m_entity->GetCenter().y, player_center.x - m_entity->GetCenter().x));
		start_angle = MAMA::Angle180(start_angle);

		if (abs(start_angle - MAMA::Angle180(m_entity->GetAngle()) + 90) < 15)
		{
			m_entity->GetAIState()->PushState(RANGEATTACK);
			return;
		}
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
