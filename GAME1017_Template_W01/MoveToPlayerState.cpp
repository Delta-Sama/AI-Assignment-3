#include "MoveToPlayerState.h"

#include "CollisionManager.h"
#include "EnemyManager.h"

MoveToPlayerState::MoveToPlayerState(Enemy* enemy) : BehaviorState(enemy)
{

}

MoveToPlayerState::~MoveToPlayerState() = default;

void MoveToPlayerState::Enter()
{
	m_entity->SetStatus(MOVETOPLAYER);
}

void MoveToPlayerState::Update()
{
	SDL_FPoint player_center = ENMA::GetPlayer()->GetCenter();

	bool haveTunnelLOS = COMA::TunnelLOSCheck(&m_entity->GetCenter(), &player_center, TUNNEL_ENTITY_WIDTH);
	bool playerIsNear = m_entity->GetPlayerDetectRad();
	bool inMeleeDistance = MAMA::SquareDistance(&player_center, &m_entity->GetCenter()) < pow(MELEE_DIST, 2);

	if (haveTunnelLOS and playerIsNear)
	{
		if (not inMeleeDistance)
		{
			m_entity->Seek(player_center);
		}
		else
		{
			m_entity->GetAIState()->PushState(MELEEATTACK);
		}
	}
}

void MoveToPlayerState::Transition()
{
	bool haveTunnelLOS = COMA::TunnelLOSCheck(&m_entity->GetCenter(), &ENMA::GetPlayer()->GetCenter(), TUNNEL_ENTITY_WIDTH);
	bool playerIsNear = m_entity->GetPlayerDetectRad();

	if (not haveTunnelLOS or not playerIsNear)
	{
		m_entity->GetAIState()->ChangeState(MOVETOLOS);
		return;
	}
}

void MoveToPlayerState::Exit()
{

}