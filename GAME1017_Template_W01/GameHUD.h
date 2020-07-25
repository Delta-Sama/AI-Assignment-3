#pragma once
#ifndef _GAMEHUD_H_
#define _GAMEHUD_H_

#include "PlayerHealthBar.h"
#include "Player.h"

class GameHUD
{
public:
	GameHUD(Player* player);
	~GameHUD();

	void Update();
	void Clean();
	void Render();

private:
	PlayerHealthBar* m_healthBar;
	Label* m_enemiesLeft;
	Label* m_enemiesKilled;

	int m_enemiesCounter;
	
};

#endif