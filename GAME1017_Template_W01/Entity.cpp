#include "Entity.h"
#include "Engine.h"

#include <algorithm>

Entity::Entity(SDL_Rect s, SDL_FRect d, SDL_Texture* t, float maxHealth) : GameObject(s, d, t), m_maxHealth(maxHealth)
, m_health(maxHealth), m_projectileTime(0)
{
	m_moveEngine = new EntityMoveEngine(this);
}

Entity::~Entity()
{
	if (GetAnimator() != nullptr)
	{
		GetAnimator()->Clean();
		delete GetAnimator();
		AddAnimator(nullptr);
	}
	if (m_moveEngine != nullptr)
		delete m_moveEngine;
}

void Entity::SetBodyPosition()
{
	m_body.x = GetDstP()->x + (GetDstP()->w - m_body.w) / 2;
	m_body.y = GetDstP()->y + (GetDstP()->h - m_body.h) / 2;
}

void Entity::SetX(float x) { m_dst.x = x - (m_dst.w - m_body.w) / 2; }
void Entity::SetY(float y) { m_dst.y = y - (m_dst.h - m_body.h) / 2; }

void Entity::MovementUpdate()
{
	m_moveEngine->Update();
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
	Animation* damagedAnim = GetAnimator()->GetAnimation("damaged");
	
	if (damagedAnim)
		m_damaged = 2 * damagedAnim->GetMaxFrames() * damagedAnim->GetFramesFrequency()/10;
}
