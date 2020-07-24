#pragma once
#ifndef _TILE_H_
#define _TILE_H_
#include "GameObject.h"
#include "Sprite.h"
#include "Pathing.h"
#include "Label.h"

class Tile : public GameObject
{
public:
	Tile(SDL_Rect s, SDL_FRect d, SDL_Texture* t, const bool obst, const bool haz, const bool rot)
		: GameObject(s, d, t), m_obstacle(obst), m_hazard(haz), m_rotatable(rot)
	{
		//m_node = nullptr;
		m_lCost = m_lX = m_lY = nullptr;
	}
	bool& IsObstacle() { return m_obstacle; }
	bool IsHazard() { return m_hazard; }
	bool Rotatable() { return m_rotatable; }
	
	virtual void update() override {};
	virtual void clean() override {};
	
	Tile* Clone() { return new Tile(m_src, m_dst, m_pText, m_obstacle, m_hazard, m_rotatable); }
	//PathNode* Node() { return m_node; }
public:
	//PathNode* m_node;
	Label* m_lCost, * m_lX, * m_lY;
private:
	bool m_obstacle, m_hazard, m_rotatable;
};
#endif
