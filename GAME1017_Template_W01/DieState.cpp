#include "DieState.h"

#include "SoundManager.h"

DieState::DieState(Enemy* enemy) : BehaviorState(enemy)
{

}

DieState::~DieState() = default;

void DieState::Enter()
{
	SOMA::PlaySound("dead", 0, 5);
	m_entity->GetAnimator()->PlayFullAnimation("die");

	m_entity->GetHealthBar()->SetEnabled(false);

	m_entity->SetStatus(DIE);
}

void DieState::Update()
{
	if (m_entity->GetAnimator()->AnimationIsPlaying("die"))
	{
		m_entity->GetMoveEngine()->Stop();
	}
	else
	{
		m_entity->Clean();
	}
}

void DieState::Transition()
{

}

void DieState::Exit()
{

}