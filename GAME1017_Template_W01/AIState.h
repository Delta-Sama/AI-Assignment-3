#pragma once
#ifndef _AISTATE_H_
#define _AISTATE_H_

class Enemy;
enum Status;

class BehaviorState
{
public:
	BehaviorState(Enemy* enemy);
	~BehaviorState();

	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Test() = 0;
	virtual void Exit() = 0;

protected:
	Enemy* m_entity;

};

class AIState
{
public:
	AIState(Enemy* enemy);
	~AIState();

	void Update();

	void ChangeState(BehaviorState* newState);
	void ChangeState(Status status);
	
private:
	BehaviorState* m_state;
	Enemy* m_entity;

};

//States:

class IdleState : public BehaviorState
{
public:
	IdleState(Enemy* enemy);
	~IdleState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Test() override;
	virtual void Exit() override;

private:


};

class PatrolState : public BehaviorState
{
public:
	PatrolState(Enemy* enemy);
	~PatrolState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Test() override;
	virtual void Exit() override;

private:


};

class MoveToLOSState : public BehaviorState
{
public:
	MoveToLOSState(Enemy* enemy);
	~MoveToLOSState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Test() override;
	virtual void Exit() override;

private:


};

class DieState : public BehaviorState
{
public:
	DieState(Enemy* enemy);
	~DieState();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Test() override;
	virtual void Exit() override;

private:

};

#include "Enemy.h"

#endif