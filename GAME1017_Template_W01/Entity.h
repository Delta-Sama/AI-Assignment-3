#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "EntityMoveEngine.h"
#include "GameObject.h"
#include "LocalPathManager.h"

class Animator;

class Entity : public GameObject
{
public:
	Entity(SDL_Rect s, SDL_FRect d, SDL_Texture* t, float maxHealth);
	~Entity();
	
	virtual void Update() = 0;
	virtual void Clean() = 0;

	void MovementUpdate();
	Animator* GetAnimator() { return animator; }
	EntityMoveEngine* GetMoveEngine() { return m_moveEngine; }
	void AddAnimator(Animator* animator);

	void SetX(float y);
	void SetY(float y);

	SDL_FRect* GetBody() { return &m_body; }

	float GetHealth() { return m_health; }
	float GetMaxHealth() { return m_maxHealth; }

	void TakeDamage(float damage);

protected:
	Animator* animator;
	EntityMoveEngine* m_moveEngine;
	
	float m_health;
	const float m_maxHealth;
	
	SDL_FRect m_body;
	void SetBodyPosition();

	int m_projectileTime;
	int m_meleeTime;

	int m_damaged;
};

#include "Animator.h"

#endif