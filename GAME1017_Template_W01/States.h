#pragma once
#ifndef _STATES_H_
#define _STATES_H_

#include "Animator.h"
#include "Label.h"
#include "Button.h"
#include "Debug.h"
#include "Player.h"
#include "Tile.h"

#include <SDL.h>
#include <vector>
#include <array>

#define ROWS 24
#define COLS 32

class State // This is the abstract base class for all specific states.
{
protected:
	State() {}
public:
	virtual void Update() = 0; // Having at least one 'pure virtual' method like this, makes a class abtract.
	virtual void Render();     // Meaning we cannot create objects of the class.
	virtual void Enter() = 0;  // Virtual keyword means we can override in derived class.
	virtual void Exit() = 0;
	virtual void Resume();
};

class TitleState : public State
{
public:
	TitleState();
	void Update();
	void Render();
	void Enter();
	void Exit();
private:
	std::vector<Label*> m_labels;

	PlayButton* m_playButton;
};

class GameState : public State
{
public:
	GameState();
	void Update();
	void CheckCollision();
	void Render();
	void Enter();
	void Exit();
	void Resume();

private:
	DebugMode* m_debugger;
	Player* m_player;

	std::map<char, Tile*> m_tiles;
	std::array<std::array<Tile*, COLS>, ROWS> m_level;
};

class EndState : public State
{
public:
	EndState();
	void Update();
	void Render();
	void Enter();
	void Exit();
private:
	
};

#endif