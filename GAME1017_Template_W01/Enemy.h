#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.h"
#include "HealthBar.h"
#include "States.h"

enum Status { IDLE, PATROL, ATTACK, FLEE};

const float SPEED = 1;
const int MAXCHECK = 2;
const int PREVNODESSIZE = 4;
const float DETECTRADIUS = 100;

struct LocalPathManager
{
	LocalPathManager()
	{
		for (int i = 0; i < PREVNODESSIZE; i++)
		{
			prevNode[i] = nullptr;
		}
		prevCheck = 0;
		goalCounter = 0;
	}
	void CleanNodes()
	{
		for (int i = 0; i < PREVNODESSIZE; i++)
		{
			prevNode[i] = nullptr;
		}
	}
	PathNode* prevNode[PREVNODESSIZE];
	int prevCheck;
	int goalCounter;
};

class Enemy : public Entity
{
public:
	Enemy(SDL_Texture* t, Vec2 pos, float maxHealth);
	~Enemy();
	
	virtual void update() = 0;
	virtual void clean() override;
	virtual void MakeDecision() = 0;

	void EnemyUpdate();
	void Seek(SDL_FPoint& goal);
	
	bool GetPlayerLOS() { return m_playerLOS; }
	bool GetPlayerDetectRad() { return m_playerDetectRad; }
	PathNode* GetGoal() { return m_goal; }
	Status GetStatus() { return m_status; }
	
	void SetStatus(Status stat) { m_status = stat; }

	int movement[2] = { 0,0 };
	
protected:
	bool m_playerLOS;
	bool m_playerDetectRad;
	
	bool m_reachedGoal;
	PathNode* m_goal;
	LocalPathManager m_pathManager;

	Status m_status;

	HealthBar* m_healthBar;
};

#endif