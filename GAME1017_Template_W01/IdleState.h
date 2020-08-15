#pragma once
#ifndef _IDLESTATE_H_
#define _IDLESTATE_H_
#include "AIState.h"

class IdleState : public BehaviorState
{
public:
	IdleState(Enemy* enemy);
	~IdleState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Transition() override;
	virtual void Exit() override;

private:


};

#endif