#include "States.h"

#include "CollisionManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Engine.h"

#include "MathManager.h"
#include "Pathing.h"
#include "PathManager.h"

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>



#include "EnemyManager.h"
#include "EventManager.h"
#include "GameObjectManager.h"
#include "Level1.h"
#include "Tile.h"

void print(std::string msg)
{
	std::cout << msg << "\n";
}

// Begin State. CTRL+M+H and CTRL+M+U to turn on/off collapsed code.
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
	m_labels.push_back(new Label("Title",250,50, "Maxim Dobrivskiy",{0,0,255,255}));
	m_labels.push_back(new Label("Title", 350, 100, "101290100", { 100,100,255,255 }));

	m_playButton = new PlayButton({0,0,512,200},{300,250,424,120});
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

	ENMA::AddEnemy(REDSNIPER, { 10,3 });
	ENMA::AddEnemy(REDSNIPER, { 16,7 });
	
	m_level = new Level1();
	m_level->Load();
}

void GameState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_H))
	{
		m_debugger->SetMode(!m_debugger->GetMode());
	}
	
	m_player->update();

	ENMA::Update();

	CheckCollision();
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

	ENMA::Render();

	m_debugger->Draw();
	
	m_player->Render();
}

void GameState::Exit()
{
	delete m_player;
	delete m_debugger;

	ENMA::Clean();
	m_level.Clean();
	delete m_level;
}

void GameState::Resume() {}

// End GameState.

EndState::EndState()
{
}

void EndState::Enter()
{
	
}

void EndState::Update()
{
	
}

void EndState::Render()
{
	SDL_RenderClear(Engine::Instance().GetRenderer());


	
	State::Render();
}

void EndState::Exit()
{
	
}
//End EndState