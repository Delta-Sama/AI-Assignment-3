#include "Enemy.h"


#include "CollisionManager.h"
#include "EnemyManager.h"
#include "TextureManager.h"

Enemy::Enemy(SDL_Texture* t, Vec2 pos) : Entity({0,0,34,34},{pos.x * 48,pos.y * 48,60,60},t)
{
	this->m_body = { 0,0,35,35 };
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
	
}

void Enemy::clean()
{
	
}
