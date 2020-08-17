#include "States.h"

#include "CollisionManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Engine.h"
#include "MathManager.h"
#include "Pathing.h"
#include "PathManager.h"
#include "EnemyManager.h"
#include "EventManager.h"
#include "GameObjectManager.h"
#include "Level1.h"
#include "ProjectileManager.h"
#include "StateManager.h"
#include "Tile.h"
#include "UIManager.h"
#include "Util.h"

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

void print(std::string msg)
{
	std::cout << msg << "\n";
}

// Begin State.
void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}
void State::Resume() {}
// End State.

// Begin TitleState.
TitleState::TitleState() {}

void TitleState::Enter()
{
	m_labels.push_back(new Label("Title",200,50, "Maxim Dobrivskiy",{0,0,255,255}));
	m_labels.push_back(new Label("Title", 300, 100, "101290100", { 100,100,255,255 }));

	m_playButton = new PlayButton({278,250,424,120});
}

void TitleState::Update()
{
	m_playButton->Update();
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 228, 100, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	for (Label* label : m_labels)
	{
		label->Render();
	}

	m_playButton->Render();
	
	State::Render();
}

void TitleState::Exit()
{
	for (Label* label : m_labels)
	{
		delete label;
	}

	delete m_playButton;
}
// End TitleState.

// Begin GameState.

GameState::GameState()
{
	
}

void GameState::Enter()
{
	m_debugger = new DebugMode(this);

	m_player = new Player();

	m_gameHUD = new GameHUD(m_player);

	m_level = new Level1(this);
	m_level->Load();
	
	ENMA::SetPlayer(m_player);
}

void GameState::Update()
{	
	if (EVMA::KeyPressed(SDL_SCANCODE_H))
	{
		m_debugger->SetMode(!m_debugger->GetMode());
	}

	if (EVMA::KeyPressed(SDL_SCANCODE_L))
	{
		for (Enemy* enemy : *ENMA::GetEnemies())
		{
			if (enemy->GetStatus() == LEAVING)
				enemy->GetAIState()->ChangeState(IDLE);
			else
				enemy->GetAIState()->ChangeState(LEAVING);
		}
	}
	
	m_player->Update();

	m_gameHUD->Update();
	
	ENMA::Update();
	PAMA::Update();
	UIMA::Update();
	PRMA::Update();
	GOMA::Update();
	
	CheckCollision();
	
	if (m_player->GetHealth() <= 0)
	{
		STMA::ChangeState(new EndState);
		return;
	}
	if (ENMA::GetEnemies()->empty())
	{
		STMA::ChangeState(new WinState);
		return;
	}
}

void GameState::CheckCollision()
{
	COMA::CheckMapCollision(m_player);
	
	ENMA::CheckCollision();
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 64, 128, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	m_level->Render();

	GOMA::Render();
	ENMA::Render();
	
	m_player->Render();

	PRMA::Render();

	m_gameHUD->Render();

	m_debugger->Draw();
	Util::Draw();
	
	UIMA::Render(LOW);
	UIMA::Render(MEDIUM);
	UIMA::Render(HIGH);
	
}

void GameState::Exit()
{
	delete m_player;
	delete m_debugger;

	m_gameHUD->Clean();
	delete m_gameHUD;
	
	ENMA::Clean();
	GOMA::Clean();
	UIMA::Clean();
	PRMA::Clean();
	
	m_level->Clean();
	delete m_level;

	ENMA::SetPlayer(nullptr);
}

void GameState::Resume() {}

// End GameState.

EndState::EndState()
{
}

void EndState::Enter()
{
	m_restartButton = new RestartButton( { 278,250,424,120 });
	m_exitButton = new ExitButton({ 278,420,424,120 });

}

void EndState::Update()
{
	if (m_restartButton->Update() == 1)
		return;
	if (m_exitButton->Update() == 1)
		return;
}

void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 128, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	m_restartButton->Render();
	m_exitButton->Render();
	
	State::Render();
}

void EndState::Exit()
{
	delete m_exitButton;
	delete m_restartButton;
}

// Win state:

WinState::WinState()
{
}

void WinState::Enter()
{
	m_restartButton = new RestartButton({ 278,250,424,120 });
	m_exitButton = new ExitButton({ 278,420,424,120 });
	m_winLabel = new Sprite({ 0,0,800,250 }, { (WIDTH - 600) / 2, 40, 600, 200 }, TEMA::GetTexture("win_label"));
}

void WinState::Update()
{
	if (m_restartButton->Update() == 1)
		return;
	if (m_exitButton->Update() == 1)
		return;
}

void WinState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 160, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	m_restartButton->Render();
	m_exitButton->Render();
	m_winLabel->Render();

	State::Render();
}

void WinState::Exit()
{
	delete m_exitButton;
	delete m_restartButton;
	delete m_winLabel;
}

//End EndState
