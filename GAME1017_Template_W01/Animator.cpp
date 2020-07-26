#include "Animator.h"

Animator::Animator(Entity* animEntity)
{
	this->m_entity = animEntity;
	this->m_curAnimationPriority = 0;
	this->m_faceSide = 0;
	this->m_animFrame = 0;
	this->m_maxAnimationFrames = 0;
	this->m_lastFrameTime = 0;
}

void Animator::SetNextAnimation(const std::string& type)
{
	Animation* anim = m_animationsMap[type];
	Animation* nextAnim = m_animationsMap[m_nextAnimation];
	if ((nextAnim == nullptr) or (anim->GetPriotity() >= nextAnim->GetPriotity()))
	{
		m_nextAnimation = type;
	}
}

void Animator::PlayAnimation()
{
	if (m_animationsMap[m_nextAnimation] != nullptr)
	{
		Animation* anim = m_animationsMap[m_nextAnimation];
		if (m_curAnimType != m_nextAnimation)
		{
			m_curAnimationPriority = anim->GetPriotity();
			m_animFrame = 0;
			m_lastFrameTime = 0;
			m_curAnimType = m_nextAnimation;
			m_maxAnimationFrames = anim->GetMaxFrames();
		}
		//std::cout << SDL_GetTicks() - lastFrameTime << " vs " << anim->getFramesFrequency() << "\n";
		if (SDL_GetTicks() - m_lastFrameTime >= anim->GetFramesFrequency())
		{
			m_lastFrameTime = SDL_GetTicks();
			if (m_entity == nullptr)
				std::cout << "No entity!!!!!!!!!\n";
			m_entity->SetSrcCords(anim->GetStartX() + anim->GetMoveX() * m_animFrame, anim->GetStartY() + anim->GetMoveY() * m_faceSide);
			if (++m_animFrame >= m_maxAnimationFrames)
			{
				m_animFrame = 0;
			}
		}
	}
	m_nextAnimation = "";
}

void Animator::AddAnimation(const std::string& key, Uint32 maxFrames, Uint32 priority, Uint32 moveX, Uint32 moveY, Uint32 startX
	, Uint32 startY, Uint32 framesFrequency)
{
	m_animationsMap[key] = new Animation(maxFrames, priority, moveX, moveY, startX, startY, framesFrequency);
}

void Animator::Clean()
{
	for (auto animPare : m_animationsMap)
	{
		delete animPare.second;
	}
}

Animation* Animator::GetAnimation(const std::string& key)
{
	return m_animationsMap[key];
}

Animation::Animation(Uint32 maxFrames, Uint32 priority, Uint32 moveX, Uint32 moveY, Uint32 startX, Uint32 startY, Uint32 framesFrequency)
{
	this->m_startX = startX;
	this->m_startY = startY;
	this->m_maxFrames = maxFrames;
	this->m_moveX = moveX;
	this->m_moveY = moveY;
	this->m_priority = priority;
	this->m_framesFrequency = framesFrequency*10;
}
