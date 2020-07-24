#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "GameObject.h"

class Animator;

class Entity : public GameObject
{
public:
	Entity(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	
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
	
private:
	Vec2 m_velocity;
	Vec2 m_accel;
	float m_maxVelocity;
	
	float m_drag, m_speed;
	Animator* animator;

protected:
	SDL_FRect m_body;
	void SetBodyPosition();
};

#include "Animator.h"

#endif