#include "SlimeProjectile.h"
#include "TextureManager.h"

#include <iostream>

const float SLIMEDAMAGE = 15.0;
const float SLIMESPEED = 7.0;
const float w = 27.0;
const float h = 45.0;

SlimeProjectile::SlimeProjectile(SDL_FPoint start, SDL_FPoint direction, Side side)
	: Projectile({ 0,0,18,30 }, {start.x - w / 2, start.y - h / 2,w,h},
		TEMA::GetTexture("slime"),SLIMESPEED, direction, side, SLIMEDAMAGE)
{
	this->m_animFrequency = 8;
	this->m_animMaxFrames = 3;
	this->m_animCurFrame = 0;
	this->m_animFreqCounter = 0;
	this->m_animXMove = 18;

	this->m_prevStatus = ACTIVE;
}

SlimeProjectile::~SlimeProjectile()
{
	
}

void SlimeProjectile::Update()
{
	m_prevStatus = m_status;
	
	switch (m_status)
	{
	case ACTIVE:
		{
			this->m_dst.x += this->m_direction.x * m_speed;
			this->m_dst.y += this->m_direction.y * m_speed;

			if (this->m_animFreqCounter++ >= this->m_animFrequency)
			{
				this->m_animFreqCounter = 0;
				this->m_animCurFrame++;
				if (this->m_animCurFrame == this->m_animMaxFrames)
					this->m_animCurFrame = 0;
				this->m_src.x = this->m_animCurFrame * this->m_animXMove;
			}
			this->CheckCollision();
			break;
		}
	case DYING:
		{
		
			if (m_prevStatus == ACTIVE)
			{
				std::cout << "Prev was active\n";
				this->m_animCurFrame = 0;
				this->m_animFreqCounter = 0;
				this->m_animMaxFrames = 5;
				this->m_animFrequency = 8;
			}
			if (this->m_animFreqCounter++ >= this->m_animFrequency)
			{
				this->m_animFreqCounter = 0;
				this->m_animCurFrame++;
				if (this->m_animCurFrame == this->m_animMaxFrames)
					this->m_status = DIED;
				this->m_src.x = this->m_animCurFrame * this->m_animXMove;
				this->m_src.y = this->m_src.h;
			}
			break;
		}
	case DIED:
		{
			m_active = false;
			break;
		}
	default:
		break;
	}
}
