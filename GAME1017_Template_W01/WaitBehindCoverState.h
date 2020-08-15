#pragma once
#ifndef _WAITBEHINDCOVERSTATE_H_
#define _WAITBEHINDCOVERSTATE_H_
#include "AIState.h"

class WaitBehindCoverState : public BehaviorState
{
public:
	WaitBehindCoverState(Enemy* enemy);
	~WaitBehindCoverState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Transition() override;
	virtual void Exit() override;

private:
	int m_frames;

};

#endif