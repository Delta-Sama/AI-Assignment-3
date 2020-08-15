#pragma once
#ifndef _REDSNIPER_H_
#define _REDSNIPER_H_
#include "Enemy.h"

const float SNIPERMAXHEALTH = 100.0;

class RedSniper : public Enemy
{
public:
	RedSniper(Vec2 pos);
	~RedSniper();

	virtual void Update() override;
	virtual void MakeDecision() override;
	virtual void Melee() override;
	virtual void ShootProjectile(float dirX, float dirY) override;
	
private:
	
};

#endif