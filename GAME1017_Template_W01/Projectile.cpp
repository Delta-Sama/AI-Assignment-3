#include "Projectile.h"
#include "MathManager.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "CollisionManager.h"

#include <iostream>

#include "GameObjectManager.h"

Projectile::Projectile(SDL_Rect s, SDL_FRect d, SDL_Texture* t, float speed, SDL_FPoint direction, Side side, float damage) : Sprite(s,d,t)
{
	this->m_speed = speed;
	this->m_direction = direction;
	this->m_side = side;

	this->SetAngle(MAMA::Rad2Deg(MAMA::AngleBetweenPoints(direction.y,direction.x)) + 90);

	this->m_active = true;
	this->m_damage = damage;
	this->m_status = ACTIVE;
}

Projectile::~Projectile()
{
	
}

void Projectile::CheckCollision()
{
	if (m_side == PLAYERSIDE)
	{
		for (Enemy* enemy : *ENMA::GetEnemies())
		{
			if (COMA::AABBCheck(m_dst, *enemy->GetDstP()))
			{
				enemy->TakeDamage(m_damage);
				m_status = DYING;
				break;
			}
		}
	}
	else
	{
		if (COMA::AABBCheck(m_dst, *ENMA::GetPlayer()->GetDstP()))
		{
			ENMA::GetPlayer()->TakeDamage(m_damage);
			m_status = DYING;
		}
	}

	for (Tile* tile : *GameObjectManager::GetCollidableTiles())
	{
		if (COMA::AABBCheck(m_dst, *tile->GetDstP()))
		{
			m_status = DYING;
			break;
		}
	}
}

void Projectile::Update()
{
	if (m_status == ACTIVE)
	{
		this->m_dst.x += this->m_direction.x * m_speed;
		this->m_dst.y += this->m_direction.y * m_speed;

		this->CheckCollision();
	}
}

void Projectile::Clean()
{
	
}
