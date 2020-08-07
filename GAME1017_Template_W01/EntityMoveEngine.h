#pragma once
#ifndef _ENTITYMOVEENGINE_H_
#define _ENTITYMOVEENGINE_H_

#include "Vector2.h"

class Entity;

class EntityMoveEngine
{
public:
	EntityMoveEngine(Entity* entity);
	~EntityMoveEngine();

	void Update();
	
	void Stop();
	void StopX();
	void StopY();
	void SetAccelX(float a);
	void SetAccelY(float a);

	float GetVelX();
	float GetVelY();
	
private:
	Vec2 m_velocity;
	Vec2 m_accel;
	float m_maxVelocity;

	float m_drag, m_speed;

	Entity* m_entity;
	
};

#include "Entity.h"

#endif