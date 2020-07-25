#pragma once
#ifndef _PROJECTILEMANAGER_H_
#define _PROJECTILEMANAGER_H_

#include "Projectile.h"

#include <vector>

class ProjectileManager
{
public:
	static void Update();
	static void Render();
	
	static void AddProjectile(Projectile* proj);
	static std::vector<Projectile*>* GetProjectiles() { return &s_projectiles; }
	static void Init();
	
private:
	static std::vector<Projectile*> s_projectiles;

	static SDL_Point m_windowSize;
};

typedef ProjectileManager PRMA;

#endif