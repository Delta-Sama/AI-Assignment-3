#include "RangeAttackState.h"

#include "EnemyManager.h"

RangeAttackState::RangeAttackState(Enemy* enemy) : BehaviorState(enemy)
{}

RangeAttackState::~RangeAttackState() = default;

void RangeAttackState::Enter()
{
	m_lifetime = WAITAFTERATTACK;
}

void RangeAttackState::Update()
{
	if (m_lifetime-- == WAITAFTERATTACK)
	{
		if ((m_entity->GetRangeTime() + ENEMYRANGETIME) >= Engine::Instance().GetFrames())
		{
			m_lifetime = 0;
			return;
		}

		float moveX = cos(MAMA::Deg2Rad(m_entity->GetAngle() - 90));
		float moveY = sin(MAMA::Deg2Rad(m_entity->GetAngle() - 90));
		m_entity->ShootProjectile(moveX, moveY);
	}
	float angle = MAMA::AngleBetweenPoints((ENMA::GetPlayer()->GetCenter().y - m_entity->GetCenter().y), (ENMA::GetPlayer()->GetCenter().x - m_entity->GetCenter().x));
	double dif = m_entity->SetSmoothAngle(angle);
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
