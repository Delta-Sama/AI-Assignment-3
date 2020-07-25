#include "HealthBar.h"
#include "Engine.h"
#include "TextureManager.h"
#include "UIManager.h"

HealthBar::HealthBar(Entity* entity) : UIObject({0,0,200,35},{100,17,0,0},TEMA::GetTexture("healthBar"), HIGH)
{
	m_entity = entity;
	m_scale = new Sprite({0,0,200,35},{100,17,0,0},TEMA::GetTexture("healthBarScale"));

	UIMA::AddObject(this);
}

void HealthBar::Update()
{
	this->m_dst.x = m_entity->GetCenter().x - this->m_dst.w / 2;
	this->m_dst.y = m_entity->GetCenter().y - this->m_dst.h / 1.5;

	m_scale->GetDstP()->x = m_entity->GetCenter().x - m_scale->GetDstP()->w / 2;
	m_scale->GetDstP()->y = m_entity->GetCenter().y - m_scale->GetDstP()->h / 1.5;
}

void HealthBar::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_scale->GetTexture(), &m_src, &m_dst);
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_pText, &m_src, &m_dst);
}

void HealthBar::Clean()
{
	delete m_scale;
}
