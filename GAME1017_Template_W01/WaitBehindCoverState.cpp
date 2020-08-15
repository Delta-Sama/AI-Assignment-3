#include "WaitBehindCoverState.h"

#include "CollisionManager.h"
#include "EnemyManager.h"

WaitBehindCoverState::WaitBehindCoverState(Enemy* enemy) : BehaviorState(enemy)
{

}

WaitBehindCoverState::~WaitBehindCoverState() = default;

void WaitBehindCoverState::Enter()
{
	m_frames = WAITBEHINDCOVERTIME;
}

void WaitBehindCoverState::Update()
{

}

void WaitBehindCoverState::Transition()
{
	if (--m_frames == 0)
	{
		m_entity->GetAIState()->ChangeState(MOVETOLOS);
		return;
	}
	if (COMA::TunnelLOSCheck(&m_entity->GetCenter(), &ENMA::GetPlayer()->GetCenter(), TUNNELENTITYWIDTH))
	{
		m_entity->GetAIState()->ChangeState(MOVETOCOVER);
		return;
	}
}

void WaitBehindCoverState::Exit()
{

}