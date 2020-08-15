#pragma once
#ifndef _DIESTATE_H_
#define _DIESTATE_H_
#include "AIState.h"

class DieState : public BehaviorState
{
public:
	DieState(Enemy* enemy);
	~DieState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Transition() override;
	virtual void Exit() override;

private:

};

#endif