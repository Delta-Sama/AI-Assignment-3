#include "RangeAttackState.h"

#include "EnemyManager.h"

RangeAttackState::RangeAttackState(Enemy* enemy) : BehaviorState(enemy)
{}

RangeAttackState::~RangeAttackState() = default;

void RangeAttackState::Enter()
{
	m_lifetime = WAIT_AFTER_ATTACK;
}

void RangeAttackState::Update()
{
	float angle = MAMA::AngleBetweenPoints((ENMA::GetPlayer()->GetCenter().y - m_entity->GetCenter().y), (ENMA::GetPlayer()->GetCenter().x - m_entity->GetCenter().x));
	double dif = m_entity->SetSmoothAngle(angle);
	if (m_lifetime-- == WAIT_AFTER_ATTACK)
	{
		if ((m_entity->GetRangeTime() + ENEMY_RANGE_TIME) >= Engine::Instance().GetFrames())
		{
			m_lifetime = 0;
			return;
		}

		float moveX = cos(MAMA::Deg2Rad(m_entity->GetAngle() - 90));
		float moveY = sin(MAMA::Deg2Rad(m_entity->GetAngle() - 90));
		m_entity->ShootProjectile(moveX, moveY);
	}
}

void RangeAttackState::Transition()
{
	if (m_lifetime <= 0)
	{
		m_entity->GetAIState()->PopState();
		return;
	}
}

void RangeAttackState::Exit()
{
	
}
