#pragma once
#ifndef _FLEESTATE_H_
#define _FLEESTATE_H_
#include "AIState.h"

class FleeState : public BehaviorState
{
public:
	FleeState(Enemy* enemy);
	~FleeState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Transition() override;
	virtual void Exit() override;

private:
	

};

#endif