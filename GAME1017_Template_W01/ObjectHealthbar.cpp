#include "ObjectHealthbar.h"

#include <iostream>



#include "Engine.h"
#include "TextureManager.h"
#include "UIManager.h"

const float w = 50.0;
const float h = 7.0;

ObjectHealthBar::ObjectHealthBar(Obstacle* obstacle)
: UIObject({ 0,0,200,35 }, { 0,0,w,h }, TEMA::GetTexture("healthBar"), HIGH)
{
	m_obstacle = obstacle;
	m_scale = new Sprite({ 0,0,200,35 }, { 0,0,w,h }, TEMA::GetTexture("healthBarScale"));

	UIMA::AddObject(this);
}

void ObjectHealthBar::Update()
{
	this->m_dst.x = m_obstacle->GetCenter().x - this->m_dst.w / 2;
	this->m_dst.y = m_obstacle->GetCenter().y - this->m_dst.h * 4.5;

	m_scale->GetDstP()->x = this->m_dst.x;
	m_scale->GetDstP()->y = this->m_dst.y;
	
	m_scale->GetDstP()->w = ((float)m_obstacle->GetHealth() / m_obstacle->GetMaxHealth()) * w;
}

void ObjectHealthBar::Render()
{
	if (m_enabled and m_obstacle->GetHealth() < m_obstacle->GetMaxHealth())
	{
		SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_pText, &m_src, &m_dst);
		SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_scale->GetTexture(), &*m_scale->GetSrcP(), &*m_scale->GetDstP());
	}
}

void ObjectHealthBar::Clean()
{
	delete m_scale;
}
