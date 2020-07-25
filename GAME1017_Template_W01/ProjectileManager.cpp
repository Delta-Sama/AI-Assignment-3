#include "ProjectileManager.h"

#include <iostream>


#include "Engine.h"

std::vector<Projectile*> PRMA::s_projectiles;
SDL_Point PRMA::m_windowSize;

void ProjectileManager::Init()
{
	SDL_GetWindowSize(Engine::Instance().GetWindow(), &m_windowSize.x, &m_windowSize.y);
}

void ProjectileManager::Update()
{
	for (std::vector<Projectile*>::iterator proj = s_projectiles.begin(); proj != s_projectiles.end();)
	{
		if (!(*proj)->GetActive())
		{
			delete *proj;
			proj = s_projectiles.erase(proj);
		}
		else
		{
			(*proj)->Update();
			SDL_FRect* temp = (*proj)->GetDstP();
			
			if (temp->x < 0 - temp->w or temp->x > m_windowSize.x or temp->y < 0 - temp->h or temp->y > m_windowSize.y)
			{
				std::cout << "Removed\n";
				(*proj)->SetActive(false);
			}
			proj++;
		}
	}
}

void ProjectileManager::Render()
{
	for (Projectile* proj : s_projectiles)
	{
		proj->Render();
	}
}

void ProjectileManager::AddProjectile(Projectile* proj)
{
	s_projectiles.push_back(proj);
}
