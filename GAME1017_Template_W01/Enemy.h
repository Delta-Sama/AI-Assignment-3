#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.h"
#include "HealthBar.h"
#include "States.h"

enum Status { IDLE, PATROL, ATTACK, FLEE, DIE};

const float SPEED = 1;

class Enemy : public Entity
{
public:
	Enemy(SDL_Texture* t, Vec2 pos, float maxHealth);
	~Enemy();
	
	virtual void Update() = 0;
	virtual void Clean() override;
	virtual void MakeDecision() = 0;

	void EnemyUpdate();
	void Seek(SDL_FPoint& goal);
	
	Status GetStatus() { return m_status; }
	bool GetActive() { return m_active; }
	bool GetPlayerLOS() { return m_playerLOS; }
	bool GetPlayerDetectRad() { return m_playerDetectRad; }
	
	LocalPathManager* GetPathManager() { return &m_pathManager; }
	PathNode* GetGoal() { return m_goal; }
	bool GoalIsReached() { return m_reachedGoal; }
	
	void SetGoal(PathNode* newGoal) { m_goal = newGoal; }
	void SetReachedGoal(bool result) { m_reachedGoal = result; }

	void CleanLocalPath();
	
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
	
	bool m_active;
};

#endif