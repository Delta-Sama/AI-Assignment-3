#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.h"
#include "States.h"

enum Status { IDLE, PATROL, ATTACK, FLEE};

class Enemy : public Entity
{
public:
	Enemy(SDL_Texture* t, Vec2 pos);
	~Enemy();
	
	virtual void update() override;
	virtual void clean() override;
	virtual void MakeDecision() = 0;

	bool GetPlayerLOS() { return m_playerLOS; }

	int movement[2] = { 0,0 };

	PathNode* GetGoal() { return m_goal; }
protected:
	bool m_playerLOS;
	Status m_status;
	bool m_reachedGoal;
	PathNode* m_goal;
};

#endif