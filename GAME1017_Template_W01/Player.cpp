#include "Player.h"

#include "Engine.h"
#include "TextureManager.h"

#include <algorithm>
#include <iostream>

#include "EventManager.h"
#include "MathManager.h"
#include "ProjectileManager.h"
#include "SlimeProjectile.h"
#include "SoundManager.h"

const float PROJCOOLDOWN = 0.4;

Player::Player()
	:Entity({0,0,34,34}, {100,100,60,60}, TEMA::GetTexture("player"), PLAYERMAXHEALTH)
{
	this->m_body = {0,0,35,35};
	this->SetBodyPosition();
	
	this->addAnimator(new Animator(this));

	this->getAnimator()->addAnimation("idle", 3, 1, 34, 0, 0, 0,16);
	this->getAnimator()->addAnimation("run", 8, 2, 34, 0,0,34);
	
	std::cout << "Player created\n";
}

Player::~Player()
{
	if (this->getAnimator() != nullptr)
		delete this->getAnimator();
}

void Player::update()
{
	this->movement[0] = 0;
	this->movement[1] = 0;

	SDL_Point mouse = EVMA::GetMousePos();
	float dx = mouse.x - this->m_dst.x;
	float dy = mouse.y - this->m_dst.y;
	float hyp = sqrt(dx * dx + dy * dy);
	float dirX = dx / hyp;
	float dirY = dy / hyp;
	
	if (EVMA::KeyHeld(SDL_SCANCODE_A))
	{
		this->SetAccelX(-1.0f);
		this->movement[0] = -1;
		this->getAnimator()->setFace(1);
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_D))
	{
		this->SetAccelX(1.0f);
		this->movement[0] = 1;
		this->getAnimator()->setFace(0);
	}
	if (EVMA::KeyHeld(SDL_SCANCODE_W))
	{
		this->movement[1] = 1;
		this->SetAccelY(-1.0f);
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_S))
	{
		this->movement[1] = -1;
		this->SetAccelY(1.0f);
	}
	if (EVMA::MousePressed(3))
	{
		if ((m_projectileTime + PROJCOOLDOWN * 1000) < SDL_GetTicks())
		{
			SOMA::PlaySound("projectile", 0, 1);
			m_projectileTime = SDL_GetTicks();

			float dist = 25.0;
			SDL_FPoint projPos = { this->GetCenter().x + dirX * dist,this->GetCenter().y + dirY * dist};
			
			PRMA::AddProjectile(new SlimeProjectile(projPos, { dirX , dirY }, PLAYERSIDE));
		}
	}
	
	if (this->movement[0] == 0 and this->movement[1] == 0)
		this->getAnimator()->setNextAnimation("idle");
	else
		this->getAnimator()->setNextAnimation("run");

	float angle = MAMA::AngleBetweenPoints(dy,dx);
	
	this->SetAngle(MAMA::Rad2Deg(angle) + 90);
	
	this->getAnimator()->playAnimation();
	
	movementUpdate();
	
	this->SetBodyPosition();
}

void Player::clean()
{
	
}