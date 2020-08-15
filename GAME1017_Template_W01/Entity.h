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

	virtual void Melee() = 0;
	virtual void ShootProjectile(float dirX, float dirY) = 0;

	void MovementUpdate();
	Animator* GetAnimator() { return animator; }
	EntityMoveEngine* GetMoveEngine() { return m_moveEngine; }
	void AddAnimator(Animator* animator);

	void SetX(float y);
	void SetY(float y);
	bool IsMoving() { return m_moveEngine->GetVelX() != 0 or m_moveEngine->GetVelY() != 0; }

	double SetSmoothAngle(float angle);

	SDL_FRect* GetBody() { return &m_body; }

	float GetHealth() { return m_health; }
	float GetMaxHealth() { return m_maxHealth; }

	Uint64 GetMeleeTime() { return m_meleeTime; }
	Uint64 GetRangeTime() { return m_projectileTime; }
	
	void TakeDamage(float damage);

protected:
	Animator* animator;
	EntityMoveEngine* m_moveEngine;
	
	float m_health;
	const float m_maxHealth;
	
	SDL_FRect m_body;
	void SetBodyPosition();

	Uint64 m_projectileTime;
	Uint64 m_meleeTime;

	int m_damaged;
};

#include "Animator.h"

#endif