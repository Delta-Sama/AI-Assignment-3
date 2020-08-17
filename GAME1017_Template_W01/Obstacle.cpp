#include "Obstacle.h"

#include <iostream>


#include "TextureManager.h"

Obstacle::Obstacle(SDL_Rect s, SDL_FRect d, SDL_Texture* t, ObstacleType type) : GameObject(s, d, t), m_type(type)
, m_destructable(false), m_health(1), m_maxHealth(1), m_active(true)
{
	animator.maxHittedEffect = 0;
	animator.framesFrequency = 0;
	animator.status = EXIST;

	m_healthBar = new ObjectHealthBar(this);
}

Obstacle::~Obstacle() = default;

void Obstacle::Update()
{
}

void Obstacle::Clean()
{
	delete m_healthBar;
}

void Obstacle::TakeDamage(int dmg)
{
	if (m_destructable)
	{
		m_health - dmg > 0 ? m_health -= dmg : m_health = 0;
		if (m_health > 0)
		{
			animator.Reset();
		}
		else
		{
			if (animator.status == EXIST)
				animator.Destruct();
		}
	}
}

Barrel::Barrel(Vec2 pos) : Obstacle({0,0,29,38},{pos.x,pos.y,29,38},TEMA::GetTexture("barrel"), BARREL)
{
	m_destructable = true;
	m_health = m_maxHealth = 100;
	
	animator.maxHittedEffect = 4;
	animator.framesFrequency = 4;

	animator.maxDyingEffect = 5;
	animator.dyingEffect = animator.maxDyingEffect;
	animator.dyingFramesFrequency = 6;
}

Barrel::~Barrel() = default;

void Barrel::Update()
{
	if (animator.hittedEffect > 0 and animator.status == EXIST)
	{
		if (animator.frame++ >= animator.framesFrequency)
		{
			animator.frame = 0;
			animator.hittedEffect--;

			m_angle = -7 + rand()%15;
		}
		if (animator.hittedEffect == 0)
		{
			m_angle = 0;
		}
	}
	if (animator.dyingEffect < animator.maxDyingEffect)
	{
		if (animator.frame++ >= animator.framesFrequency)
		{
			animator.frame = 0;
			animator.dyingEffect++;

			m_angle = -12 + rand() % 25;
			
			m_src.x = m_src.w * animator.dyingEffect;
		}
		if (animator.dyingEffect == animator.maxDyingEffect)
		{
			m_active = false;
			animator.status = DESTRUCTED;
		}
	}
	
}
