#pragma once
#ifndef _MOVETOPLAYERSTATE_H_
#define _MOVETOPLAYERSTATE_H_
#include "AIState.h"

class MoveToPlayerState : public BehaviorState
{
public:
	MoveToPlayerState(Enemy* enemy);
	~MoveToPlayerState();

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