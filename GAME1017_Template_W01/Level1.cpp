#include "Level1.h"

#include "MathManager.h"
#include "PathManager.h"
#include "States.h"
#include "TextureManager.h"
#include "EnemyManager.h"
#include "GameObjectManager.h"

#include <fstream>

const int TILESIZE = 32;

void Level1::Load()
{
	SDL_Texture* m_pTileText = TEMA::GetTexture("tiles");
	std::ifstream inFile("Data/Tiledata.txt");

	if (inFile.is_open())
	{ // Create map of Tile prototypes.
		char key;
		int x, y;
		bool obst, haz, rot;
		while (!inFile.eof())
		{
			inFile >> key >> x >> y >> obst >> haz >> rot;
			m_tiles.emplace(key, new Tile({ x * 34, y * 34, 32, 32 }, { 0,0,TILESIZE,TILESIZE }, m_pTileText, obst, haz, rot));
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
				tile->GetDstP()->x = (float)(TILESIZE * col);
				tile->GetDstP()->y = (float)(TILESIZE * row);
				// Instantiate the labels for each tile.
				tile->m_lCost = new Label("Title", tile->GetDstP()->x + 4, tile->GetDstP()->y + 18, " ", { 0,0,0,255 });
				tile->m_lX = new Label("Title", tile->GetDstP()->x + 18, tile->GetDstP()->y + 2, std::to_string(col).c_str(), { 0,0,0,255 });
				tile->m_lY = new Label("Title", tile->GetDstP()->x + 2, tile->GetDstP()->y + 2, std::to_string(row).c_str(), { 0,0,0,255 });
				// Construct the Node for a valid tile.
				
				if (tile->IsObstacle())
					GameObjectManager::AddCollidableTile(tile);
				else
					GameObjectManager::AddBackgroundTile(tile);
				
				if (tile->Rotatable())
					tile->SetAngle(90.0 * (rand() % 4));
			}
		}
	}
	inFile.close();

	// Nodes:
	inFile.open("Data/Nodes.txt");
	if (inFile.is_open())
	{
		char key;
		for (int row = 0; row < ROWS; row++)
		{
			for (int col = 0; col < COLS; col++)
			{
				inFile >> key;
				if (key == 'n' or key == 'p')
				{
					PathNode* newNode = PAMA::CreateNode(col, row);
					if (key == 'p')
					{
						m_patrolPath.push_back(newNode);
					}
				}
			}
		}
	}
	inFile.close();
	// -------- //

	// Obstacles:
	inFile.open("Data/Obstacles.txt");
	if (inFile.is_open())
	{
		char key;
		for (int row = 0; row < ROWS; row++)
		{
			for (int col = 0; col < COLS; col++)
			{
				inFile >> key;
				if (key == 'b')
				{
					GOMA::CreateObstacle(BARREL, { (float)(TILESIZE * col) ,(float)(TILESIZE * row) });
					std::cout << "Obstacle created\n";
				}
			}
		}
	}
	inFile.close();
	// -------- //
	
	ENMA::SetScene(m_scene);
	
	ENMA::AddEnemy(REDSNIPER, { 10,3 }, (rand() % 12) * 30);
	ENMA::AddEnemy(REDSNIPER, { 16,7 }, (rand() % 12) * 30);
	ENMA::AddEnemy(REDSNIPER, { 4,10 }, (rand() % 12) * 30);
	/*ENMA::AddEnemy(REDSNIPER, { 8,7 }, (rand() % 12) * 30);
	ENMA::AddEnemy(REDSNIPER, { 2,5 }, (rand() % 12) * 30);
	ENMA::AddEnemy(REDSNIPER, { 9,5 }, (rand() % 12) * 30);*/
}

void Level1::Render()
{
	
}

void Level1::Clean()
{
	
}