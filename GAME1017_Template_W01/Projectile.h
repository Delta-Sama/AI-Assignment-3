#pragma once
#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "Sprite.h"

enum Side { ENEMYSIDE, PLAYERSIDE };
enum ProjStatus { ACTIVE, DYING, DIED };

class Projectile : public Sprite
{
public:
	~Projectile();
	
	virtual void Update();
	void Clean();
	
	void CheckCollision();

	void SetActive(bool active) { m_active = active; }

	bool GetActive() { return m_active; }

	SDL_FRect* GetBody() { return &m_body; }
	void SetBodyPosition();
	
protected:
	Projectile(SDL_Rect s, SDL_FRect d, SDL_Texture* t, float speed, SDL_FPoint direction, Side side, float damage);
	
	bool m_active;
	float m_damage;
	float m_speed;
	SDL_FPoint m_direction;
	Side m_side;
	ProjStatus m_status;

	SDL_FRect m_body;
	
};

#endif