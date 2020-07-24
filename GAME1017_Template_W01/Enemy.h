#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(SDL_Texture* t, Vec2 pos);
	~Enemy();
	
	virtual void update() override;
	virtual void clean() override;

	int movement[2] = { 0,0 };
private:
	
};

#endif