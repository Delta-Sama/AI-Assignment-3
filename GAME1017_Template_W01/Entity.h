#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "GameObject.h"
#include "LocalPathManager.h"

class Animator;

class Entity : public GameObject
{
public:
	Entity(SDL_Rect s, SDL_FRect d, SDL_Texture* t, float maxHealth);
	
	virtual void update() = 0;
	virtual void clean() = 0;

	void Stop();
	void StopX();
	void StopY();
	void SetAccelX(float a);
	void SetAccelY(float a);
	
	float GetVelX();
	float GetVelY();
	void SetX(float y);
	void SetY(float y);
	void movementUpdate();
	Animator* getAnimator() { return animator; }
	void addAnimator(Animator* animator);

	SDL_FRect* GetBody() { return &m_body; }

	float GetHealth() { return m_health; }
	float GetMaxHealth() { return m_maxHealth; }

	void TakeDamage(float damage);
	
private:
	Vec2 m_velocity;
	Vec2 m_accel;
	float m_maxVelocity;
	
	float m_drag, m_speed;
	Animator* animator;

protected:
	float m_health;
	const float m_maxHealth;
	
	SDL_FRect m_body;
	void SetBodyPosition();

	int m_projectileTime;
	
	int m_dying = 0;
};

#include "Animator.h"

#endif