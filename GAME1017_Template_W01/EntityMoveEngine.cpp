#include "EntityMoveEngine.h"
#include "Engine.h"

#include <algorithm>


EntityMoveEngine::EntityMoveEngine(Entity* entity) : m_entity(entity), m_drag(STANDART_DRAG), m_maxVelocity(MAX_ENTITY_VELOCITY)
{
	m_accel.x = m_accel.y = m_velocity.x = m_velocity.y = 0.0;
}

EntityMoveEngine::~EntityMoveEngine() = default;

void EntityMoveEngine::Update()
{
	m_velocity.x += m_accel.x;
	m_velocity.x *= m_drag;
	m_velocity.x = std::min(std::max(m_velocity.x, -m_maxVelocity), (m_maxVelocity));

	// Y axis
	m_velocity.y += m_accel.y;
	m_velocity.y *= m_drag;
	m_velocity.y = std::min(std::max(m_velocity.y, -m_maxVelocity), (m_maxVelocity));

	m_entity->GetDstP()->x += (int)m_velocity.x;
	m_entity->GetDstP()->y += (int)m_velocity.y;

	m_accel.x = m_accel.y = 0.0;

	if (abs(m_velocity.x) < 0.01)
		m_velocity.x = 0;
	if (abs(m_velocity.y) < 0.01)
		m_velocity.y = 0;

	// Check X boundary
	if (m_entity->GetDstP()->x < 0)
	{
		m_entity->GetDstP()->x = 0;
	}
	else if (m_entity->GetDstP()->x > WIDTH - m_entity->GetDstP()->w)
	{
		m_entity->GetDstP()->x = WIDTH - m_entity->GetDstP()->w;
	}
	// Check Y boundary
	if (m_entity->GetDstP()->y < 0)
	{
		m_entity->GetDstP()->y = 0;
	}
	else if (m_entity->GetDstP()->y > HEIGHT - m_entity->GetDstP()->h)
	{
		m_entity->GetDstP()->y = HEIGHT - m_entity->GetDstP()->h;
	}
}

void EntityMoveEngine::Stop()
{
	StopX();
	StopY();
}

void EntityMoveEngine::StopX() { m_velocity.x = 0.0; }
void EntityMoveEngine::StopY() { m_velocity.y = 0.0; }

void EntityMoveEngine::SetAccelX(float a) { m_accel.x = a; }
void EntityMoveEngine::SetAccelY(float a) { m_accel.y = a; }
float EntityMoveEngine::GetVelX() { return m_velocity.x; }
float EntityMoveEngine::GetVelY() { return m_velocity.y; }