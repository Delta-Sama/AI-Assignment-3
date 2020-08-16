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

	virtual void Update() override;
	virtual void Clean() override;
	virtual void Melee() override;
	virtual void ShootProjectile(float dirX, float dirY) override;
	
	void KeyboardInput();
	void GamepadInput();

private:
	
};

#endif