#include "FleeState.h"

#include "EnemyManager.h"

FleeState::FleeState(Enemy* enemy) : BehaviorState(enemy)
{}

FleeState::~FleeState() = default;

void FleeState::Enter()
{
	
}

void FleeState::Update()
{
	m_entity->Flee();
}

void FleeState::Transition()
{
	bool isFarAway = MAMA::SquareDistance(&ENMA::GetPlayer()->GetCenter(), &m_entity->GetCenter()) > pow(MELEE_DIST*4, 2);
	
	if (isFarAway)
	{
		m_entity->GetAIState()->ChangeState(LEAVING);
		return;
	}
}

void FleeState::Exit()
{
	
}
