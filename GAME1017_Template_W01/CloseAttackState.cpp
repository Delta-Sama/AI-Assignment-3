#include "CloseAttackState.h"


#include "EnemyManager.h"
#include "SoundManager.h"

CloseAttackState::CloseAttackState(Enemy* enemy) : BehaviorState(enemy)
{}

CloseAttackState::~CloseAttackState() = default;

void CloseAttackState::Enter()
{
	m_lifetime = WAIT_AFTER_ATTACK;
}

void CloseAttackState::Update()
{
	if (m_lifetime-- == WAIT_AFTER_ATTACK)
	{
		if ((m_entity->GetMeleeTime() + ENEMY_MELEE_TIME) >= Engine::Instance().GetFrames())
		{
			m_lifetime = 0;
			return;
		}
		m_entity->Melee();
	}
	float angle = MAMA::AngleBetweenPoints((ENMA::GetPlayer()->GetCenter().y - m_entity->GetCenter().y), (ENMA::GetPlayer()->GetCenter().x - m_entity->GetCenter().x));
	double dif = m_entity->SetSmoothAngle(angle);
}

void CloseAttackState::Transition()
{
	if (m_lifetime <= 0)
	{
		m_entity->GetAIState()->PopState();
		return;
	}
	if (m_entity->GetHealth() < m_entity->GetMaxHealth() * 0.25)
	{
		m_entity->GetAIState()->ChangeState(FLEE);
		return;
	}
}

void CloseAttackState::Exit()
{
	
}
