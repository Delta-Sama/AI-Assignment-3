#include "States.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "SoundManager.h"
#include "StateManager.h" // Make sure this is NOT in "States.h" or circular reference.
#include "TextureManager.h"
#include "Engine.h"

#include <iostream>
#include <ctime>

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

	m_player = new Player({0,0,128,64},{ 100,100,128,64 });
}

void GameState::Update()
{
	m_player->update();
}

void GameState::CheckCollision()
{
	
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 64, 128, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	m_player->Render();
}

void GameState::Exit()
{
	delete m_player;
	delete m_debugger;
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