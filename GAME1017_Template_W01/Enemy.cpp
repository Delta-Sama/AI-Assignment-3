#include "Enemy.h"

#include "TextureManager.h"

Enemy::Enemy(SDL_Texture* t, Vec2 pos) : Entity({0,0,34,34},{pos.x * 32,pos.y * 32,68,68},t)
{
	this->m_body = { 0,0,40,40 };
	this->SetBodyPosition();

	std::cout << "Enemy created\n";
}

Enemy::~Enemy()
{
	if (this->getAnimator() != nullptr)
		delete this->getAnimator();
}

void Enemy::update()
{
	movementUpdate();

	this->SetBodyPosition();
}

void Enemy::clean()
{
	
}
