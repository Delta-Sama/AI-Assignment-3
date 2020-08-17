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

#include "Util.h"

const int PROJCOOLDOWN = FPS * 0.4;
const float PROJDAMAGE = 10.0;

const float MELEECOOLDOWN = FPS * 0.6;
const float MELEEDAMAGE = 15.0;

Player::Player()
	:Entity({0,0,34,34}, {100,100,60,60}, TEMA::GetTexture("player"), PLAYERMAXHEALTH)
{
	m_body = {0,0,35,35};
	this->SetBodyPosition();

	this->SetType(PLAYER);
	
	this->AddAnimator(new Animator(this));
	
	this->GetAnimator()->AddAnimation("idle", 3, 1, 34, 0, 0, 0,16);
	this->GetAnimator()->AddAnimation("run", 8, 2, 34, 0,0,34,6);
	this->GetAnimator()->AddAnimation("die", 4, 3, 34, 0, 0, 68,6);
	this->GetAnimator()->AddAnimation("melee", 6, 3, 34, 0, 0, 102,3);
	this->GetAnimator()->AddAnimation("run_melee", 6, 3, 34, 0, 0, 136, 3);
}

Player::~Player()
{
	
}

void Player::Update()
{
	m_moveEngine->SetMove(false);
	
	if (SDL_NumJoysticks() < 1)
		this->KeyboardInput();
	else
		this->GamepadInput();
	
	this->GetAnimator()->Update();
	
	MovementUpdate();
	
	this->SetBodyPosition();

	if (not IsMoving())
		this->GetAnimator()->SetNextAnimation("idle");
	else
		this->GetAnimator()->SetNextAnimation("run");
}

void Player::Clean()
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

	float angle = MAMA::AngleBetweenPoints(dy, dx);
	SetSmoothAngle(angle);

	float moveX = cos(MAMA::Deg2Rad(GetAngle() - 90));
	float moveY = sin(MAMA::Deg2Rad(GetAngle() - 90));

	/*if (EVMA::KeyHeld(SDL_SCANCODE_A))
	{
		this->GetMoveEngine()->SetAccelX(-1.0f);
		m_movement[0] = -1;
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_D))
	{
		this->GetMoveEngine()->SetAccelX(1.0f);
		m_movement[0] = 1;
	}*/
	if (EVMA::KeyHeld(SDL_SCANCODE_W))
	{
		this->GetMoveEngine()->SetAccelX(moveX);
		this->GetMoveEngine()->SetAccelY(moveY);
		m_moveEngine->SetMove(true);
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_S))
	{
		this->GetMoveEngine()->SetAccelX(-moveX);
		this->GetMoveEngine()->SetAccelY(-moveY);
		m_moveEngine->SetMove(true);
	}
	
	if (EVMA::MousePressed(1))
	{
		this->Melee();
	}
	if (EVMA::MousePressed(3))
	{
		this->ShootProjectile(moveX, moveY);
	}
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
			this->GetMoveEngine()->SetAccelX(-1.0f);
			m_moveEngine->SetMove(true);
		}
		else if (EVMA::GetGameController(0)->LEFT_STICK_X > deadZone)
		{
			this->GetMoveEngine()->SetAccelX(1.0f);
			m_moveEngine->SetMove(true);
		}
		if (EVMA::GetGameController(0)->LEFT_STICK_Y > deadZone)
		{
			this->GetMoveEngine()->SetAccelY(-1.0f);
			m_moveEngine->SetMove(true);
		}
		else if (EVMA::GetGameController(0)->LEFT_STICK_Y < -deadZone)
		{
			this->GetMoveEngine()->SetAccelY(1.0f);
			m_moveEngine->SetMove(true);
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
	if ((m_meleeTime + MELEECOOLDOWN) < Engine::Instance().GetFrames())
	{
		if (not this->IsMoving())
			this->GetAnimator()->PlayFullAnimation("melee");
		else
			this->GetAnimator()->PlayFullAnimation("run_melee");
		
		SOMA::PlaySound("melee", 0, 3);
		
		m_meleeTime = Engine::Instance().GetFrames();
		
		bool hit = false;
		for (Enemy* enemy : *ENMA::GetEnemies())
		{
			if (MAMA::SquareDistance(&GetCenter(), &enemy->GetCenter()) < pow(MELEE_DIST, 2))
			{
				
				float dy = enemy->GetBody()->y - m_body.y;
				float dx = enemy->GetBody()->x - m_body.x;
				
				if (abs(MAMA::Angle180(MAMA::Rad2Deg(MAMA::AngleBetweenPoints(dy, dx)) + 90 - m_angle)) < MELEE_ANGLE)
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
	if ((m_projectileTime + PROJCOOLDOWN) < Engine::Instance().GetFrames())
	{
		SOMA::PlaySound("projectile", 0, 1);
		m_projectileTime = Engine::Instance().GetFrames();

		float dist = 25.0;
		SDL_FPoint projPos = { this->GetCenter().x + dirX * dist,this->GetCenter().y + dirY * dist };

		PRMA::AddProjectile(new SlimeProjectile(projPos, { dirX , dirY }, PLAYERSIDE));
	}
}