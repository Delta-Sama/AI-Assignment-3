#include "Engine.h"
#include "CollisionManager.h"
#include "DebugManager.h"
#include "EventManager.h"
#include "FontManager.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "ProjectileManager.h"

#include <iostream>


#include "EnemyManager.h"
#include "UIManager.h"

using namespace std;

Engine::Engine() :m_running(false), m_pBNull(false) { cout << "Engine class constructed!" << endl; }

bool Engine::Init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	cout << "Initializing game..." << endl;
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != nullptr) // Window init success.
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != nullptr) // Renderer init success.
			{
				EVMA::Init();
				SOMA::Init();
				TEMA::Init();
				PRMA::Init();
			}
			else return false; // Renderer init fail.
		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	m_frames = 0;
	m_fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.

	TEMA::RegisterTexture("Img/PlayB.png", "play_button");
	TEMA::RegisterTexture("Img/ResumeB.png", "resume_button");
	TEMA::RegisterTexture("Img/RestartB.png", "restart_button");
	TEMA::RegisterTexture("Img/ExitB.png", "exit_button");
	TEMA::RegisterTexture("Img/YouWon.png","win_label");
	
	TEMA::RegisterTexture("Img/Player.png", "player");
	TEMA::RegisterTexture("Img/Enemy.png", "enemy");
	TEMA::RegisterTexture("Img/CloseEnemy.png", "melee_enemy");
	TEMA::RegisterTexture("Img/TileMap.png", "tiles");
	TEMA::RegisterTexture("Img/HealthBar.png", "healthBar");
	TEMA::RegisterTexture("Img/HealthBarScale.png", "healthBarScale");
	TEMA::RegisterTexture("Img/Slime.png", "slime");
	TEMA::RegisterTexture("Img/RedSlime.png", "redslime");
	TEMA::RegisterTexture("Img/Barrel.png", "barrel");
	
	TEMA::RegisterTexture("Img/ExitB.png", "exit_b");
	
	FOMA::RegisterFont("Img/TITLEFONT.otf", "Title", 50);
	FOMA::RegisterFont("Img/TITLEFONT.otf", "SmallTitle", 35);
	
	SOMA::Load("Audio/projectile.wav", "projectile", SOUND_SFX);
	SOMA::SetSoundVolume(40,1);
	SOMA::Load("Audio/projDamage.wav", "projDamage", SOUND_SFX);
	SOMA::SetSoundVolume(40, 2);
	SOMA::Load("Audio/melee.wav", "melee", SOUND_SFX);
	SOMA::SetSoundVolume(90, 3);
	SOMA::Load("Audio/sharpDamage.wav", "sharpDamage", SOUND_SFX);
	SOMA::SetSoundVolume(40, 4);
	SOMA::Load("Audio/dead.wav", "dead", SOUND_SFX);
	SOMA::SetSoundVolume(20, 5);
	SOMA::Load("Audio/obstacleBreak.mp3", "obst_dest", SOUND_SFX);
	SOMA::SetSoundVolume(10, 6);
	
	SOMA::Load("Audio/papyrus.mp3", "background", SOUND_MUSIC);
	SOMA::SetMusicVolume(11);//18);
	SOMA::PlayMusic("background");
	
	STMA::ChangeState(new TitleState);
	SOMA::AllocateChannels(16);
	m_running = true; // Everything is okay, start the engine.
	cout << "Engine Init success!" << endl;
	return true;
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;
	if (m_delta < m_fps) // Engine has to sleep.
		SDL_Delay(m_fps - m_delta);
}

void Engine::HandleEvents()
{
	EVMA::HandleEvents();
}

void Engine::Update()
{
	m_frames++;
	STMA::Update();
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer); // Clear the screen with the draw color.
	// Draw anew.
	STMA::Render();
	SDL_RenderPresent(m_pRenderer);
}

void Engine::Clean()
{
	cout << "Cleaning game." << endl;
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	DEMA::Quit();
	EVMA::Quit();
	FOMA::Quit();
	SOMA::Quit();
	STMA::Quit();
	TEMA::Quit();
	UIMA::Clean();
	ENMA::Clean();
	IMG_Quit();
	SDL_Quit();
}

int Engine::Run()
{
	if (m_running) // What does this do and what can it prevent?
		return -1;
	if (Init("Comso Bugs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (m_running) // Main engine loop.
	{
		Wake();
		HandleEvents();
		Update();
		Render();
		if (m_running)
			Sleep();
	}
	Clean();
	return 0;
}

Engine& Engine::Instance()
{
	static Engine instance; // C++11 will prevent this line from running more than once. Magic statics.
	return instance;
}

SDL_Renderer* Engine::GetRenderer() { return m_pRenderer; }
bool& Engine::Running() { return m_running; }


bool& Engine::isNull() { return m_pBNull; }
void Engine::setNull() { m_pBNull = true; }

void Engine::setRunning(bool x)
{
	m_running = x;
}