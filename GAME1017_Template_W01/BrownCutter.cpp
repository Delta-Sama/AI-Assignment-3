#include "BrownCutter.h"

#include "CollisionManager.h"
#include "EnemyManager.h"
#include "MathManager.h"
#include "ProjectileManager.h"
#include "SlimeProjectile.h"
#include "SoundManager.h"
#include "TextureManager.h"

BrownCutter::BrownCutter(Vec2 pos) : Enemy(TEMA::GetTexture("enemy"), pos, CUTTERMAXHEALTH, MELEETYPE)
{
	this->AddAnimator(new Animator(this));

	this->GetAnimator()->AddAnimation("idle", 3, 1, 34, 0, 0, 0, 16);
	this->GetAnimator()->AddAnimation("run", 8, 2, 34, 0, 0, 34);
	this->GetAnimator()->AddAnimation("die", 4, 5, 34, 0, 0, 68);
	this->GetAnimator()->AddAnimation("damaged", 3, 3, 34, 0, 0, 102, 4);
	this->GetAnimator()->AddAnimation("melee", 6, 4, 34, 0, 0, 136, 4);
	this->GetAnimator()->AddAnimation("melee_run", 6, 4, 34, 0, 0, 170, 4);

	this->m_AIState->ChangeState(PATROL);
}

BrownCutter::~BrownCutter() = default;

void BrownCutter::MakeDecision()
{
	m_AIState->Update();
}

void BrownCutter::Melee()
{
	if ((GetMeleeTime() + ENEMY_MELEE_TIME) < Engine::Instance().GetFrames())
	{
		SOMA::PlaySound("melee", 0, 3);
		m_meleeTime = Engine::Instance().GetFrames();

		if (IsMoving())
			GetAnimator()->PlayFullAnimation("melee");
		else
			GetAnimator()->PlayFullAnimation("run_melee");

		bool hit = false;
		if (MAMA::SquareDistance(&GetCenter(), &ENMA::GetPlayer()->GetCenter()) < pow(MELEE_DIST, 2))
		{
			float dy = ENMA::GetPlayer()->GetBody()->y - GetBody()->y;
			float dx = ENMA::GetPlayer()->GetBody()->x - GetBody()->x;

			if (abs(MAMA::Angle180(MAMA::Rad2Deg(MAMA::AngleBetweenPoints(dy, dx)) + 90 - GetAngle())) < MELEE_ANGLE)
			{
				ENMA::GetPlayer()->TakeDamage(ENEMY_MELEE_DAMAGE);
				hit = true;
			}
		}

		if (hit)
		{
			SOMA::PlaySound("sharpDamage", 0, 5);
		}
	}
}

void BrownCutter::ShootProjectile(float dirX, float dirY)
{
	if ((m_projectileTime + ENEMY_PROJ_TIME) < Engine::Instance().GetFrames())
	{
		SOMA::PlaySound("projectile", 0, 7);
		m_projectileTime = Engine::Instance().GetFrames();

		float dist = 25.0;
		SDL_FPoint projPos = { this->GetCenter().x + dirX * dist,this->GetCenter().y + dirY * dist };

		PRMA::AddProjectile(new SlimeProjectile(projPos, { dirX , dirY }, ENEMYSIDE));
	}
}

void BrownCutter::Update()
{
	MakeDecision();

	EnemyUpdate();
}
