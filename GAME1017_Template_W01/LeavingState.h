#pragma once
#ifndef _LEAVINGSTATE_H_
#define _LEAVINGSTATE_H_
#include "AIState.h"

class LeavingState : public BehaviorState
{
public:
	LeavingState(Enemy* enemy);
	~LeavingState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Transition() override;
	virtual void Exit() override;

private:
	int m_frame;
	float dx, dy;

};

#endif