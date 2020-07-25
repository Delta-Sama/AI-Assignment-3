#include "GameHUD.h"
#include "UIManager.h"

#include <string>

#include "EnemyManager.h"

GameHUD::GameHUD(Player* player)
{
	m_healthBar = new PlayerHealthBar(player);
	
	m_enemiesLeft = new Label("SmallTitle", 350, 600, "Left: ", { 230,230,200,255 });
	m_enemiesKilled = new Label("SmallTitle", 620, 600, "Killed: ", { 230,230,200,255 });
}

GameHUD::~GameHUD()
{
}

void GameHUD::Update()
{
	std::string left = "Left: " + std::to_string(ENMA::GetEnemies()->size());
	m_enemiesLeft->SetText(left.c_str());
	std::string killed = "Killed: " + std::to_string(m_enemiesCounter);
	m_enemiesKilled->SetText(killed.c_str());
}

void GameHUD::Clean()
{
	m_healthBar->Clean();
	delete m_healthBar;
	delete m_enemiesLeft;
	delete m_enemiesKilled;
}


void GameHUD::Render()
{
	m_enemiesLeft->Render();
	m_enemiesKilled->Render();
}