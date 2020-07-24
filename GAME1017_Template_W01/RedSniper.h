#pragma once
#ifndef _REDSNIPER_H_
#define _REDSNIPER_H_
#include "Enemy.h"

class RedSniper : public Enemy
{
public:
	RedSniper(Vec2 pos);
	~RedSniper();

	virtual void update() override;
	virtual void MakeDecision() override;
	
private:
	
};

#endif