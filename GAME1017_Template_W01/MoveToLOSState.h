#pragma once
#ifndef _MOVETOLOSSTATE_H_
#define _MOVETOLOSSTATE_H_
#include "AIState.h"

class MoveToLOSState : public BehaviorState
{
public:
	MoveToLOSState(Enemy* enemy);
	~MoveToLOSState();

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