#include "RedSniper.h"


#include "CollisionManager.h"
#include "EnemyManager.h"
#include "TextureManager.h"

RedSniper::RedSniper(Vec2 pos) : Enemy(TEMA::GetTexture("enemy"), pos)
{
	this->addAnimator(new Animator(this));

	this->getAnimator()->addAnimation("idle", 3, 1, 34, 0, 0, 0, 16);
	this->getAnimator()->addAnimation("run", 8, 2, 34, 0, 0, 34);
}

RedSniper::~RedSniper()
{
	
}

void RedSniper::MakeDecision()
{
	static PathNode* prevNode = nullptr;
	switch (m_status)
	{
	case IDLE:
		
		break;
	case PATROL:
		{
			for (PathNode* patrolNode : *ENMA::GetScene()->GetLevel()->GetPatrolPath())
			{
				//if (patrolNode != )
			}
		}
		break;
	default:
		break;
	}
}

void RedSniper::update()
{
	m_playerLOS = COMA::LOSCheck(&ENMA::GetScene()->GetPlayer()->GetCenter(), &this->GetCenter());

	MakeDecision();
	
	movementUpdate();

	this->SetBodyPosition();
}
