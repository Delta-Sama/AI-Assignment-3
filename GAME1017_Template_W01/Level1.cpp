#include "Level1.h"

#include "MathManager.h"
#include "PathManager.h"
#include "States.h"
#include "TextureManager.h"

#include <fstream>

#include "GameObjectManager.h"

void Level1::Load()
{
	SDL_Texture* m_pTileText = TEMA::GetTexture("tiles");
	std::ifstream inFile("Data/Tiledata.txt");

	Sprite* m_pBling = new Sprite({ 224,64,32,32 }, { (float)(16) * 32, (float)(4) * 32, 32, 32 }, m_pTileText);

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
					GameObjectManager::AddCollidableTile(tile);
			}
		}
	}
	inFile.close();
	// Now build the graph from ALL the non-obstacle and non-hazard tiles. Only N-E-W-S compass points.
	for (int row = 0; row < ROWS; row++)
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

			m_level[row][col]->Node()->SetHeuristic(PAMA::HEuclid(m_level[row][col]->Node(), m_level[(int)(m_pBling->GetDstP()->y / 32)][(int)(m_pBling->GetDstP()->x / 32)]->Node()));
			//m_level[row][col]->Node()->SetH(PAMA::HManhat(m_level[row][col]->Node(), m_level[(int)(m_pBling->GetDstP()->y / 32)][(int)(m_pBling->GetDstP()->x / 32)]->Node()));
			m_level[row][col]->m_lCost->SetText(std::to_string((int)(m_level[row][col]->Node()->Heuristic())).c_str());
		}
	}
}

void Level1::Render()
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			m_level[row][col]->Render();
		}
	}
}

void Level1::Clean()
{
	
}