#pragma once
#ifndef _PLATFORMPLAYER_H_
#define _PLATFORMPLAYER_H_

#include "Sprite.h"
#include "Entity.h"

class Player : public Entity
{
public: // Methods
	Player(SDL_Rect s, SDL_FRect d);
	~Player();

	virtual void update() override;
	virtual void clean() override;
	
	int movement[2] = { 0,0 };
private:
	
};

#endif