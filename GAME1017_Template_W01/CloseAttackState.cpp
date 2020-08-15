#include "CloseAttackState.h"


#include "EnemyManager.h"
#include "SoundManager.h"

CloseAttackState::CloseAttackState(Enemy* enemy) : BehaviorState(enemy)
{}

CloseAttackState::~CloseAttackState() = default;

void CloseAttackState::Enter()
{
	m_lifetime = WAITAFTERATTACK;
}

void CloseAttackState::Update()
{
	if (m_lifetime-- == WAITAFTERATTACK)
	{
		if ((m_entity->GetMeleeTime() + ENEMYMELEETIME) >= Engine::Instance().GetFrames())
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
}

void CloseAttackState::Exit()
{
	
}
