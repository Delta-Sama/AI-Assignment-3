#pragma once
#ifndef _PATROLSTATE_H_
#define _PATROLSTATE_H_
#include "AIState.h"

class PatrolState : public BehaviorState
{
public:
	PatrolState(Enemy* enemy);
	~PatrolState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Transition() override;
	virtual void Exit() override;

private:


};

#endif