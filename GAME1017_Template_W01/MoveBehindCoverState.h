#pragma once
#ifndef _MOVEBEHINDCOVERSTATE_H_
#define _MOVEBEHINDCOVERSTATE_H_
#include "AIState.h"

class MoveBehindCoverState : public BehaviorState
{
public:
	MoveBehindCoverState(Enemy* enemy);
	~MoveBehindCoverState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Transition() override;
	virtual void Exit() override;

private:
	int m_update_frame;
	const int m_max_update_frame = 30;
	std::vector<PathConnection*> m_path;

};

#endif