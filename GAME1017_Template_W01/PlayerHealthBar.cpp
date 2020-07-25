#include "PlayerHealthBar.h"

const float x = 70;
const float y = 600;
const float w = 200;
const float h = 25;

PlayerHealthBar::PlayerHealthBar(Entity* player) : HealthBar(player)
{
	this->m_dst = {x,y,w,h};
	*this->m_scale->GetDstP() = { x,y,w,h };
}

void PlayerHealthBar::Update()
{
	m_scale->GetDstP()->w = (m_entity->GetHealth() / m_entity->GetMaxHealth()) * w;
}