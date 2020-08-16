#pragma once
#ifndef _BROWNCUTTER_H_
#define _BROWNCUTTER_H_
#include "Enemy.h"

const float CUTTERMAXHEALTH = 100.0;

class BrownCutter : public Enemy
{
public:
	BrownCutter(Vec2 pos);
	~BrownCutter();

	virtual void Update() override;
	virtual void MakeDecision() override;
	virtual void Melee() override;
	virtual void ShootProjectile(float dirX, float dirY) override;

private:

};

#endif