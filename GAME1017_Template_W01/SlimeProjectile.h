#pragma once
#ifndef _SLIMEPROJECTILE_H_
#define _SLIMEPROJECTILE_H_

#include "Projectile.h"

class SlimeProjectile : public Projectile
{
public:
	SlimeProjectile(SDL_FPoint start, SDL_FPoint direction, Side side);
	~SlimeProjectile();

	virtual void Update() override;
	
private:
	int m_animFrequency;
	int m_animMaxFrames;
	int m_animCurFrame;
	int m_animFreqCounter;
	int m_animXMove;
	
};

#endif