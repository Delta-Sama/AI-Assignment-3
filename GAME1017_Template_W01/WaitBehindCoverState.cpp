#include "WaitBehindCoverState.h"

#include "CollisionManager.h"
#include "EnemyManager.h"

WaitBehindCoverState::WaitBehindCoverState(Enemy* enemy) : BehaviorState(enemy)
{

}

WaitBehindCoverState::~WaitBehindCoverState() = default;

void WaitBehindCoverState::Enter()
{
	m_frames = WAIT_BEHIND_COVER_TIME;
}

void WaitBehindCoverState::Update()
{

}

void WaitBehindCoverState::Transition()
{
	if (--m_frames == 0)
	{
		m_entity->SetCoveringTime(0);
		
		if (m_entity->GetEnemyType() == MELEETYPE)
			m_entity->GetAIState()->ChangeState(MOVETOLOS);
		else if (m_entity->GetEnemyType() == RANGETYPE)
			m_entity->GetAIState()->ChangeState(MOVETORANGE);
		
		return;
	}
	if (COMA::TunnelLOSCheck(&m_entity->GetCenter(), &ENMA::GetPlayer()->GetCenter(), TUNNEL_ENTITY_WIDTH))
	{
		m_entity->GetAIState()->ChangeState(MOVETOCOVER);
		return;
	}
}

void WaitBehindCoverState::Exit()
{

}