#pragma once
#ifndef _DEBUG_H_
#define _DEBUG_H_

class GameState;

class DebugMode
{
public:
	DebugMode(GameState* scene);
	~DebugMode() = default;

	GameState* m_playScene;

	void SetMode(bool newMode) { m_mode = newMode; }
	bool GetMode() { return m_mode; }
	void Draw();

private:
	bool m_mode;

};

#include "States.h"

#endif