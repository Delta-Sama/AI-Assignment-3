#pragma once
#ifndef _AISTATE_H_
#define _AISTATE_H_

#include <vector>
#include "PathManager.h"

class Enemy;
enum Status;

class BehaviorState
{
public:
	BehaviorState(Enemy* enemy);
	~BehaviorState();

	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Transition() = 0;
	virtual void Exit() = 0;

protected:
	Enemy* m_entity;

};

class AIState
{
public:
	AIState(Enemy* enemy);
	~AIState();

	void Update();

	void ChangeState(BehaviorState* newState);
	void ChangeState(Status status);
	BehaviorState* GetNewState(Status status);

	void PushState(Status status);
	void PopState();
	
private:
	std::vector<BehaviorState*> m_states;
	Enemy* m_entity;

};

#include "Enemy.h"

#endif
