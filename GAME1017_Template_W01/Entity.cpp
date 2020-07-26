#include "Entity.h"
#include "Engine.h"

#include <algorithm>

const float MAXVELOCITY = 3.0;

Entity::Entity(SDL_Rect s, SDL_FRect d, SDL_Texture* t, float maxHealth) : GameObject(s, d, t), m_maxHealth(maxHealth)
{
	this->m_accel.x = this->m_accel.y = this->m_velocity.x = this->m_velocity.y = 0.0;
	this->m_maxVelocity = MAXVELOCITY;
	this->m_drag = 0.88;
	this->m_health = maxHealth;

	this->m_projectileTime = 0;
}

Entity::~Entity()
{
	if (this->GetAnimator() != nullptr)
	{
		this->GetAnimator()->Clean();
		delete this->GetAnimator();
		this->AddAnimator(nullptr);
	}
}

void Entity::SetBodyPosition()
{
	this->m_body.x = this->GetDstP()->x + (this->GetDstP()->w - this->m_body.w) / 2;
	this->m_body.y = this->GetDstP()->y + (this->GetDstP()->h - this->m_body.h) / 2;
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
void Entity::SetX(float x) { m_dst.x = x - (m_dst.w - m_body.w) / 2; }
void Entity::SetY(float y) { m_dst.y = y - (m_dst.h - m_body.h) / 2; }

void Entity::MovementUpdate()
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

	static int x = 0, y = 0;
	if (x == 0 or y == 0)
		SDL_GetWindowSize(Engine::Instance().GetWindow(), &x, &y);
	
	if (GetDstP()->x < 0)
	{
		GetDstP()->x = 0;
	}
	else if (GetDstP()->x > x - GetDstP()->w)
	{
		GetDstP()->x = x - GetDstP()->w;
	}
	if (GetDstP()->y < 0)
	{
		GetDstP()->y = 0;
	}
	else if (GetDstP()->y > y - GetDstP()->h)
	{
		GetDstP()->y = y - GetDstP()->h;
	}
}

void Entity::AddAnimator(Animator* animator)
{
	if (this->animator == nullptr)
		this->animator = animator;
	else
		delete animator;
}

void Entity::TakeDamage(float damage)
{
	m_health = m_health - damage;
	if (m_health < 0)
		m_health = 0;
	Animation* damagedAnim = this->GetAnimator()->GetAnimation("damaged");
	
	if (damagedAnim)
		m_damaged = damagedAnim->GetMaxFrames() * damagedAnim->GetFramesFrequency()/10;
}
