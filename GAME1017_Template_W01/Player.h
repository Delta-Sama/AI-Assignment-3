#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"
#include "PlayerHealthBar.h"

const float PLAYERMAXHEALTH = 100.0;

class Player final : public Entity
{
public: // Methods
	Player();
	~Player();

	virtual void update() override;
	virtual void clean() override;
	
	int movement[2] = { 0,0 };
private:
	
	
};

#endif