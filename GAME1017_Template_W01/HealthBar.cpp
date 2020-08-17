#include "HealthBar.h"
#include "Engine.h"
#include "TextureManager.h"
#include "UIManager.h"

const float w = 50.0;
const float h = 7.0;

HealthBar::HealthBar(Entity* entity)
: UIObject({0,0,200,35},{0,0,w,h},TEMA::GetTexture("healthBar"), HIGH,"health_bar")
{
	m_entity = entity;
	m_scale = new Sprite({0,0,200,35},{0,0,w,h},TEMA::GetTexture("healthBarScale"));

	UIMA::AddObject(this);
}

void HealthBar::Update()
{
	this->m_dst.x = m_entity->GetCenter().x - this->m_dst.w / 2;
	this->m_dst.y = m_entity->GetCenter().y - this->m_dst.h * 4.5;

	m_scale->GetDstP()->x = this->m_dst.x;
	m_scale->GetDstP()->y = this->m_dst.y;

	m_scale->GetDstP()->w = (m_entity->GetHealth() / m_entity->GetMaxHealth()) * w;
}

void HealthBar::Render()
{
	if (m_enabled)
	{
		SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_pText, &m_src, &m_dst);
		SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_scale->GetTexture(), &*m_scale->GetSrcP(), &*m_scale->GetDstP());
	}
}

void HealthBar::Clean()
{
	delete m_scale;
}
