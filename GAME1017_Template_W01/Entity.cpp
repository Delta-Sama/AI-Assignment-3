#include "Entity.h"
#include "Engine.h"

#include <algorithm>

const float MAXVELOCITY = 10.0;

Entity::Entity(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : GameObject(s, d, t)
{
	this->m_accel.x = this->m_accel.y = this->m_velocity.x = this->m_velocity.y = 0.0;
	this->m_maxVelocity = MAXVELOCITY;
	this->m_drag = 0.88;
}

void Entity::Stop()
{
	StopX();
	StopY();
}

void Entity::StopX() { m_velocity.x = 0.0; }
void Entity::StopY() { m_velocity.y = 0.0; }

void Entity::SetAccelX(float a) { m_accel.x = a; }
void Entity::SetAccelY(float a) { m_accel.y = a; }
float Entity::GetVelX() { return m_velocity.x; }
float Entity::GetVelY() { return m_velocity.y; }
void Entity::SetX(float y) { m_dst.x = y; }
void Entity::SetY(float y) { m_dst.y = y; }

void Entity::movementUpdate()
{
	m_velocity.x += m_accel.x;
	m_velocity.x *= m_drag;
	m_velocity.x = std::min(std::max(m_velocity.x, -m_maxVelocity), (m_maxVelocity));

	// Y axis
	m_velocity.y += m_accel.y;
	m_velocity.y *= m_drag;
	m_velocity.y = std::min(std::max(m_velocity.y, -m_maxVelocity), (m_maxVelocity));

	GetDstP()->x += (int)this->m_velocity.x;
	GetDstP()->y += (int)this->m_velocity.y;

	m_accel.x = m_accel.y = 0.0;

	if (GetDstP()->x < 0 + GetDstP()->w)
	{
		GetDstP()->x = 0 + GetDstP()->w;
	}
	else if (GetDstP()->x > 800 - GetDstP()->w)
	{
		GetDstP()->x = 800 - GetDstP()->w;
	}
	if (GetDstP()->y < 0 + GetDstP()->h)
	{
		GetDstP()->y = 0 + GetDstP()->h;
	}
	else if (GetDstP()->y > 600 - GetDstP()->h)
	{
		GetDstP()->y = 600 - GetDstP()->h;
	}
}

void Entity::addAnimator(Animator* animator)
{
	if (this->animator == nullptr)
		this->animator = animator;
	else
		delete animator;
}
