#pragma once
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_
#include "GameObject.h"

class ObjectHealthBar;

enum ObstacleType { BARREL };

enum ObstacleStatus { EXIST, DESTRUCTING, DESTRUCTED };

struct ObstacleDyingAnimator
{
	int hittedEffect = 0;
	int frame = 0;
	int maxHittedEffect;
	int framesFrequency;

	int dyingEffect = 0;
	int dyingFrame = 0;
	int maxDyingEffect;
	int dyingFramesFrequency;
	
	ObstacleStatus status = EXIST;

	void Reset()
	{
		hittedEffect = maxHittedEffect;
		frame = 0;
	}

	void Destruct()
	{
		dyingEffect = 0;
		dyingFrame = 0;
		status = DESTRUCTING;
	}
};

class Obstacle : public GameObject
{
public:
	Obstacle(SDL_Rect s, SDL_FRect d, SDL_Texture* t, ObstacleType type);
	~Obstacle();

	virtual void Update() = 0;
	virtual void Clean() override;

	void TakeDamage(int dmg);
	bool IsActive() { return m_active; }

	int GetHealth() { return m_health; }
	int GetMaxHealth() { return m_maxHealth; }
	
protected:
	ObstacleType m_type;
	bool m_destructable;
	
	int m_health;
	int m_maxHealth;
	
	bool m_active;

	ObstacleDyingAnimator animator;

	ObjectHealthBar* m_healthBar;
	
};

class Barrel : public Obstacle
{
public:
	Barrel(Vec2 pos);
	~Barrel();

	virtual void Update() override;
	
private:
	
	
};

#include "ObjectHealthbar.h"

#endif