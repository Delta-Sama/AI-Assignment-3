#include "Player.h"

#include "Engine.h"
#include "TextureManager.h"

#include <algorithm>
#include <iostream>

Player::Player(SDL_Rect s, SDL_FRect d)
	:Entity(s, d, TEMA::GetTexture("Player"))
{
	this->addAnimator(new Animator(this));

	this->getAnimator()->addAnimation("run", 8, 2, 34, 50);
	this->getAnimator()->addAnimation("idle", 4, 1, 34, 50, 0, 100, 12);

}

Player::~Player()
{
	if (this->getAnimator() != nullptr)
		delete this->getAnimator();
}

