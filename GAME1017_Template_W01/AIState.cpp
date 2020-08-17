#include "AIState.h"

// States headers:
#include "IdleState.h"
#include "PatrolState.h"
#include "MoveToLOSState.h"
#include "MoveToPlayerState.h"
#include "MoveBehindCoverState.h"
#include "WaitBehindCoverState.h"
#include "FleeState.h"
#include "MoveToRangeState.h"
#include "RangeAttackState.h"
#include "CloseAttackState.h"
#include "LeavingState.h"
#include "DieState.h"

#include "CollisionManager.h"
#include "EnemyManager.h"
#include "SoundManager.h"

BehaviorState::BehaviorState(Enemy* player) : m_entity(player)
{

}

BehaviorState::~BehaviorState() = default;

AIState::AIState(Enemy* player) : m_entity(player)
{
	ChangeState(IDLE);
}

AIState::~AIState() = default;

void AIState::Update()
{
	if (not m_states.empty())
	{
		m_states.back()->Update();
		m_states.back()->Transition();
	}
}

void AIState::ChangeState(BehaviorState* newState)
{
	if (not m_states.empty())
	{
		m_states.back()->Exit();
		delete m_states.back();
		m_states.pop_back();
	}
	m_states.push_back(newState);
	m_states.back()->Enter();
}

void AIState::ChangeState(Status status)
{
	ChangeState(GetNewState(status));
}

BehaviorState* AIState::GetNewState(Status status)
{
	BehaviorState* temp_state = nullptr;
	switch (status)
	{
	case IDLE:
		temp_state = new IdleState(m_entity);
		break;
	case PATROL:
		temp_state = new PatrolState(m_entity);
		break;
	case FLEE:
		temp_state = new FleeState(m_entity);
		break;
	case DIE:
		temp_state = new DieState(m_entity);
		break;
	case MOVETOLOS:
		temp_state = new MoveToLOSState(m_entity);
		break;
	case MOVETOCOVER:
		temp_state = new MoveBehindCoverState(m_entity);
		break;
	case MOVETOPLAYER:
		temp_state = new MoveToPlayerState(m_entity);
		break;
	case MOVETORANGE:
		temp_state = new MoveToRangeState(m_entity);
		break;
	case WAITBEHINDCOVER:
		temp_state = new WaitBehindCoverState(m_entity);
		break;
	case MELEEATTACK:
		temp_state = new CloseAttackState(m_entity);
		break;
	case RANGEATTACK:
		temp_state = new RangeAttackState(m_entity);
		break;
	case LEAVING:
		temp_state = new LeavingState(m_entity);
		break;
	}
	m_entity->SetStatus(status);
	
	return temp_state;
}

void AIState::PushState(Status status)
{
	BehaviorState* temp_state = GetNewState(status);

	if (temp_state)
	{
		m_states.push_back(temp_state);
		m_states.back()->Enter();
	}
}

void AIState::PopState()
{
	if (m_states.size() > 1)
	{
		m_states.back()->Exit();
		delete m_states.back();
		m_states.pop_back();
	}
}
