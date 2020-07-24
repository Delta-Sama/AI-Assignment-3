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


#include "GameObjectManager.h"
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

	SDL_Texture* m_pTileText = TEMA::GetTexture("tiles");
	std::ifstream inFile("Data/Tiledata.txt");
	
	if (inFile.is_open())
	{ // Create map of Tile prototypes.
		char key;
		int x, y;
		bool obst, haz;
		while (!inFile.eof())
		{
			inFile >> key >> x >> y >> obst >> haz;
			m_tiles.emplace(key, new Tile({ x * 32, y * 32, 32, 32 }, { 0,0,32,32 }, m_pTileText, obst, haz));
		}
	}
	inFile.close();
	
	inFile.open("Data/Level1.txt");
	if (inFile.is_open())
	{
		print("File is open!");
		char key;
		for (int row = 0; row < ROWS; row++)
		{
			for (int col = 0; col < COLS; col++)
			{
				inFile >> key;
				m_level[row][col] = m_tiles[key]->Clone(); // Prototype design pattern used.
				Tile* tile = m_level[row][col];
				tile->GetDstP()->x = (float)(32 * col);
				tile->GetDstP()->y = (float)(32 * row);
				// Instantiate the labels for each tile.
				tile->m_lCost = new Label("Title", tile->GetDstP()->x + 4, tile->GetDstP()->y + 18, " ", { 0,0,0,255 });
				tile->m_lX = new Label("Title", tile->GetDstP()->x + 18, tile->GetDstP()->y + 2, std::to_string(col).c_str(), { 0,0,0,255 });
				tile->m_lY = new Label("Title", tile->GetDstP()->x + 2, tile->GetDstP()->y + 2, std::to_string(row).c_str(), { 0,0,0,255 });
				// Construct the Node for a valid tile.
				if (!tile->IsObstacle() or tile->IsHazard())
					tile->m_node = new PathNode((int)(tile->GetDstP()->x), (int)(tile->GetDstP()->y));
				if (tile->IsObstacle())
					GameObjectManager::AddObject(tile);
			}
		}
	}
	inFile.close();
	// Now build the graph from ALL the non-obstacle and non-hazard tiles. Only N-E-W-S compass points.
	/*for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (m_level[row][col]->Node() == nullptr) // Now we can test for nullptr.
				continue; // An obstacle or hazard tile has no connections.
			// Make valid connections.
			if (row - 1 != -1 && !m_level[row - 1][col]->IsObstacle() && !m_level[row - 1][col]->IsHazard())
				m_level[row][col]->Node()->AddConnection(new PathConnection(m_level[row][col]->Node(), m_level[row - 1][col]->Node(),
					MAMA::Distance(m_level[row][col]->Node()->x, m_level[row - 1][col]->Node()->x, m_level[row][col]->Node()->y, m_level[row - 1][col]->Node()->y)));
			if (row + 1 != ROWS && !m_level[row + 1][col]->IsObstacle() && !m_level[row + 1][col]->IsHazard())
				m_level[row][col]->Node()->AddConnection(new PathConnection(m_level[row][col]->Node(), m_level[row + 1][col]->Node(),
					MAMA::Distance(m_level[row][col]->Node()->x, m_level[row + 1][col]->Node()->x, m_level[row][col]->Node()->y, m_level[row + 1][col]->Node()->y)));
			if (col - 1 != -1 && !m_level[row][col - 1]->IsObstacle() && !m_level[row][col - 1]->IsHazard())
				m_level[row][col]->Node()->AddConnection(new PathConnection(m_level[row][col]->Node(), m_level[row][col - 1]->Node(),
					MAMA::Distance(m_level[row][col]->Node()->x, m_level[row][col - 1]->Node()->x, m_level[row][col]->Node()->y, m_level[row][col - 1]->Node()->y)));
			if (col + 1 != COLS && !m_level[row][col + 1]->IsObstacle() && !m_level[row][col + 1]->IsHazard())
				m_level[row][col]->Node()->AddConnection(new PathConnection(m_level[row][col]->Node(), m_level[row][col + 1]->Node(),
					MAMA::Distance(m_level[row][col]->Node()->x, m_level[row][col + 1]->Node()->x, m_level[row][col]->Node()->y, m_level[row][col + 1]->Node()->y)));
		}
	}

	for (int row = 0; row < ROWS; row++) // "This is where the fun begins."
	{ // Update each node with the selected heuristic and set the text for debug mode.
		for (int col = 0; col < COLS; col++)
		{
			if (m_level[row][col]->Node() == nullptr)
				continue;
			if (m_hEuclid)
				m_level[row][col]->Node()->SetH(PAMA::HEuclid(m_level[row][col]->Node(), m_level[(int)(m_pBling->GetDstP()->y / 32)][(int)(m_pBling->GetDstP()->x / 32)]->Node()));
			else
				m_level[row][col]->Node()->SetH(PAMA::HManhat(m_level[row][col]->Node(), m_level[(int)(m_pBling->GetDstP()->y / 32)][(int)(m_pBling->GetDstP()->x / 32)]->Node()));
			m_level[row][col]->m_lCost->SetText(std::to_string((int)(m_level[row][col]->Node()->H())).c_str());
		}
	}*/
}

void GameState::Update()
{
	m_player->update();

	CheckCollision();
}

void GameState::CheckCollision()
{
	COMA::CheckMapCollision(m_player);
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 64, 128, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			m_level[row][col]->Render();
		}
	}

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