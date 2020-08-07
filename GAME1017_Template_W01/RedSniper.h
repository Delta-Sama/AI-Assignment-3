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
	
private:
	
};

#endif