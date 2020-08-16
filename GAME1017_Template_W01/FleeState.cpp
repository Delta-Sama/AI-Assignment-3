#include "FleeState.h"

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
	
}

void FleeState::Exit()
{
	
}
