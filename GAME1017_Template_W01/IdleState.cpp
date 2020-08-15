#include "IdleState.h"

IdleState::IdleState(Enemy* enemy) : BehaviorState(enemy)
{

}

IdleState::~IdleState() = default;

void IdleState::Enter()
{
	m_entity->GetPathManager()->CleanNodes();
	m_entity->SetGoal(nullptr);
	m_entity->GetMoveEngine()->Stop();
	m_entity->SetStatus(IDLE);
}

void IdleState::Update()
{
	m_entity->GetAnimator()->SetNextAnimation("idle");
}

void IdleState::Exit()
{

}

void IdleState::Transition()
{

}