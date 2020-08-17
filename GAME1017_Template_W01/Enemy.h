#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "AIState.h"
#include "Engine.h"
#include "Entity.h"
#include "HealthBar.h"
#include "States.h"

enum Status {
	IDLE,
	PATROL,
	MOVETOLOS,
	MOVETORANGE,
	MOVETOCOVER,
	WAITBEHINDCOVER,
	MOVETOPLAYER,
	MELEEATTACK,
	RANGEATTACK,
	FLEE,
	LEAVING,
	DIE
};

enum EnemyType {
	MELEETYPE,
	RANGETYPE
};

const float SPEED = 1;

const float ENEMYMELEECOOLDOWN = FPS * 0.6;

class Enemy : public Entity
{
public:
	Enemy(SDL_Texture* t, Vec2 pos, float maxHealth, EnemyType enemyType);
	~Enemy();
	
	virtual void Update() = 0;
	virtual void Clean() override;
	virtual void MakeDecision() = 0;

	void EnemyUpdate();
	bool Seek(SDL_FPoint& goal);
	void Flee();
	void FollowThePath(std::vector<PathConnection*>& path);

	Status GetStatus() { return m_status; }

	bool GetPlayerLOS() { return m_playerLOS; }
	bool GetPlayerDetectRad() { return m_playerDetectRad; }
	HealthBar* GetHealthBar() { return m_healthBar; }
	
	LocalPathManager* GetPathManager() { return &m_pathManager; }
	PathNode* GetGoal() { return m_goal; }
	bool GoalIsReached() { return m_reachedGoal; }
	AIState* GetAIState() { return m_AIState; }
	PathNode* GetShortestLOSNode() { return m_shortestNode; }
	
	void SetGoal(PathNode* newGoal) { m_goal = newGoal; }
	void SetReachedGoal(bool result) { m_reachedGoal = result; }

	void CleanLocalPath();
	
	void SetStatus(Status stat) { m_status = stat; }
	EnemyType GetEnemyType() { return m_enemyType; }
	
	void SetHideTime(Uint32 time) { m_hideTime = time; }
	Uint32 GetHideTime() { return m_hideTime; }

	void SetCoveringTime(Uint32 time) { m_coveringTime = time; }
	void IncrementCoveringTime() { m_coveringTime++; }
	Uint32 GetCoveringTime() { return m_coveringTime; }

	void SetCollidable(bool col) { m_collideable = col; }
	bool GetCollidable() { return m_collideable; }
	
protected:
	int m_fleeCounter = 0;
	std::vector<PathConnection*> m_fleePath;

	bool m_collideable;
	
	bool m_playerLOS;
	bool m_playerDetectRad;
	
	bool m_reachedGoal;
	PathNode* m_goal;
	LocalPathManager m_pathManager;

	Status m_status;

	HealthBar* m_healthBar;
	AIState* m_AIState;
	PathNode* m_shortestNode;

	EnemyType m_enemyType;

	Uint32 m_hideTime;
	Uint32 m_coveringTime;
};

#endif