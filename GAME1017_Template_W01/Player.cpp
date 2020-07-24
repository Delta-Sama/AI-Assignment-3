#include "Player.h"

#include "Engine.h"
#include "TextureManager.h"

#include <algorithm>
#include <iostream>

#include "EventManager.h"

Player::Player(SDL_Rect s, SDL_FRect d)
	:Entity(s, d, TEMA::GetTexture("player"))
{
	this->addAnimator(new Animator(this));

	this->getAnimator()->addAnimation("run", 6, 2, 128, 64,0,128);
	this->getAnimator()->addAnimation("idle", 1, 1, 128, 64, 0, 0);
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
	
	if (this->movement[0] == 0 and this->movement[1] == 0)
		this->getAnimator()->setNextAnimation("idle");
	else
		this->getAnimator()->setNextAnimation("run");

	this->getAnimator()->playAnimation();
	movementUpdate();
}

void Player::clean()
{
	
}