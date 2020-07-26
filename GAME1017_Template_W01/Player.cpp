#include "Player.h"
#include "Engine.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "EventManager.h"
#include "MathManager.h"
#include "ProjectileManager.h"
#include "SlimeProjectile.h"
#include "SoundManager.h"

#include <algorithm>
#include <iostream>

const float PROJCOOLDOWN = 0.4;
const float PROJDAMAGE = 10.0;

const float MELEECOOLDOWN = 0.6;
const float MELEEDIST = 60.0;
const float MELEEDAMAGE = 15.0;
const float MELEEANGLE = 50.0;

Player::Player()
	:Entity({0,0,34,34}, {100,100,60,60}, TEMA::GetTexture("player"), PLAYERMAXHEALTH)
{
	this->m_body = {0,0,35,35};
	this->SetBodyPosition();

	this->SetType(PLAYER);
	
	this->AddAnimator(new Animator(this));

	this->GetAnimator()->AddAnimation("idle", 3, 1, 34, 0, 0, 0,16);
	this->GetAnimator()->AddAnimation("run", 8, 2, 34, 0,0,34);
	this->GetAnimator()->AddAnimation("die", 4, 3, 34, 0, 0, 68);
	this->GetAnimator()->AddAnimation("melee", 6, 3, 34, 0, 0, 102,4);
	this->GetAnimator()->AddAnimation("run_melee", 6, 3, 34, 0, 0, 136, 4);
	
	std::cout << "Player created\n";
}

Player::~Player()
{
	
}

void Player::update()
{
	this->movement[0] = 0;
	this->movement[1] = 0;
	
	if (SDL_NumJoysticks() < 1)
		this->KeyboardInput();
	else
		this->GamepadInput();

	Animation* meleeAnim = this->GetAnimator()->GetAnimation("melee");
	if (m_meleeAnimFrames < meleeAnim->GetFramesFrequency()/10 * (meleeAnim->GetMaxFrames() - 1))
	{
		m_meleeAnimFrames++;
		this->GetAnimator()->SetNextAnimation(m_curMeleeAnim);
	}
	
	if (this->movement[0] == 0 and this->movement[1] == 0)
		this->GetAnimator()->SetNextAnimation("idle");
	else
		this->GetAnimator()->SetNextAnimation("run");
	
	this->GetAnimator()->PlayAnimation();
	
	MovementUpdate();
	
	this->SetBodyPosition();
}

void Player::clean()
{
	
}

void Player::KeyboardInput()
{
	SDL_Point mouse = EVMA::GetMousePos();
	float dx = mouse.x - this->GetCenter().x;
	float dy = mouse.y - this->GetCenter().y;
	float hyp = sqrt(dx * dx + dy * dy);
	float dirX = dx / hyp;
	float dirY = dy / hyp;
	
	if (EVMA::KeyHeld(SDL_SCANCODE_A))
	{
		this->SetAccelX(-1.0f);
		this->movement[0] = -1;
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_D))
	{
		this->SetAccelX(1.0f);
		this->movement[0] = 1;
	}
	if (EVMA::KeyHeld(SDL_SCANCODE_W))
	{
		this->SetAccelY(-1.0f);
		this->movement[1] = 1;
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_S))
	{
		this->SetAccelY(1.0f);
		this->movement[1] = -1;
	}
	
	if (EVMA::MousePressed(1))
	{
		this->Melee();
	}
	if (EVMA::MousePressed(3))
	{
		this->ShootProjectile(dirX, dirY);
	}

	float angle = MAMA::AngleBetweenPoints(dy, dx);
	this->SetAngle(MAMA::Rad2Deg(angle) + 90);
}

void Player::GamepadInput()
{
	float dx = EVMA::GetGameController(0)->RIGHT_STICK_X;
	float dy = EVMA::GetGameController(0)->RIGHT_STICK_Y;
	float hyp = sqrt(dx * dx + dy * dy);
	float dirX = dx / hyp;
	float dirY = dy / hyp;
	
	if (EVMA::GetGameController(0) != nullptr)
	{
		const int deadZone = 10000;
		if (EVMA::GetGameController(0)->LEFT_STICK_X < -deadZone)
		{
			this->SetAccelX(-1.0f);
			this->movement[0] = -1;
		}
		else if (EVMA::GetGameController(0)->LEFT_STICK_X > deadZone)
		{
			this->SetAccelX(1.0f);
			this->movement[0] = 1;
		}
		if (EVMA::GetGameController(0)->LEFT_STICK_Y > deadZone)
		{
			this->SetAccelY(-1.0f);
			this->movement[1] = 1;
		}
		else if (EVMA::GetGameController(0)->LEFT_STICK_Y < -deadZone)
		{
			this->SetAccelY(1.0f);
			this->movement[1] = -1;
		}

		if (EVMA::GetGameController(0)->DPAD_DOWN)
		{
			this->Melee();
		}
		if (EVMA::GetGameController(0)->DPAD_RIGHT)
		{
			this->ShootProjectile(dirX, dirY);
		}
	}

	float angle = MAMA::AngleBetweenPoints(dy, dx);
	this->SetAngle(MAMA::Rad2Deg(angle) + 90);
}

void Player::Melee()
{
	if ((m_meleeTime + MELEECOOLDOWN * 1000) < SDL_GetTicks())
	{
		m_meleeAnimFrames = 0;

		SOMA::PlaySound("melee", 0, 3);
		m_meleeTime = SDL_GetTicks();

		if (this->movement[0] == 0 and this->movement[1] == 0)
			m_curMeleeAnim = "melee";
		else
			m_curMeleeAnim = "run_melee";
		
		bool hit = false;
		for (Enemy* enemy : *ENMA::GetEnemies())
		{
			if (COMA::SquareRectDistance(m_body, *enemy->GetBody()) < pow(MELEEDIST, 2))
			{
				float dy = enemy->GetBody()->y - m_body.y;
				float dx = enemy->GetBody()->x - m_body.x;
				if (abs(MAMA::Rad2Deg(MAMA::AngleBetweenPoints(dy, dx)) + 90 - m_angle) < MELEEANGLE)
				{
					enemy->TakeDamage(MELEEDAMAGE);
					hit = true;
				}
			}
		}
		if (hit)
		{
			SOMA::PlaySound("sharpDamage", 0, 4);
		}
	}
}

void Player::ShootProjectile(float dirX, float dirY)
{
	if ((m_projectileTime + PROJCOOLDOWN * 1000) < SDL_GetTicks())
	{
		SOMA::PlaySound("projectile", 0, 1);
		m_projectileTime = SDL_GetTicks();

		float dist = 25.0;
		SDL_FPoint projPos = { this->GetCenter().x + dirX * dist,this->GetCenter().y + dirY * dist };

		PRMA::AddProjectile(new SlimeProjectile(projPos, { dirX , dirY }, PLAYERSIDE));
	}
}