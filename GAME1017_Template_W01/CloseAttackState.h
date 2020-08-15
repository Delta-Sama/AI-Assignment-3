#pragma once
#ifndef _CLOSEATTACKSTATE_H_
#define _CLOSEATTACKSTATE_H_
#include "AIState.h"

class CloseAttackState : public BehaviorState
{
public:
	CloseAttackState(Enemy* enemy);
	~CloseAttackState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Transition() override;
	virtual void Exit() override;

private:
	int m_lifetime;;

};

#endif