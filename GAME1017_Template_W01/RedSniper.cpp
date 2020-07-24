#include "RedSniper.h"

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

void RedSniper::update()
{
	
}
