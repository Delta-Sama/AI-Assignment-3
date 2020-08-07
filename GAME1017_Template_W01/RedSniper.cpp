#include "RedSniper.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "MathManager.h"
#include "TextureManager.h"

RedSniper::RedSniper(Vec2 pos) : Enemy(TEMA::GetTexture("enemy"), pos, SNIPERMAXHEALTH)
{
	this->AddAnimator(new Animator(this));

	this->GetAnimator()->AddAnimation("idle", 3, 1, 34, 0, 0, 0, 16);
	this->GetAnimator()->AddAnimation("run", 8, 2, 34, 0, 0, 34);
	this->GetAnimator()->AddAnimation("die", 4, 4, 34, 0, 0, 68);
	this->GetAnimator()->AddAnimation("damaged", 3, 3, 34, 0, 0, 102,4);
	
	m_status = IDLE;
}

RedSniper::~RedSniper()
{
	
}

void RedSniper::MakeDecision()
{
	// Call AIState->Update();
}

void RedSniper::Update()
{
	MakeDecision();

	if (m_damaged-- > 0)
	{
		this->GetAnimator()->SetNextAnimation("damaged");
	}
	
	EnemyUpdate();
}
