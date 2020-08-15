#pragma once
#ifndef _RANGEATTACKSTATE_H_
#define _RANGEATTACKSTATE_H_
#include "AIState.h"

class RangeAttackState : public BehaviorState
{
public:
	RangeAttackState(Enemy* enemy);
	~RangeAttackState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Transition() override;
	virtual void Exit() override;

private:
	int m_lifetime;;

};

#endif