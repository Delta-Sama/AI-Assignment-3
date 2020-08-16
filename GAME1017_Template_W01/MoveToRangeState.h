#pragma once
#ifndef _MOVETORANGESTATE_H_
#define _MOVETORANGESTATE_H_
#include "AIState.h"

class MoveToRangeState : public BehaviorState
{
public:
	MoveToRangeState(Enemy* enemy);
	~MoveToRangeState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Transition() override;
	virtual void Exit() override;

	void ClearPath();

private:
	int m_update_frame;
	const int m_max_update_frame = 20;
	std::vector<PathConnection*> m_path;
	
};

#endif