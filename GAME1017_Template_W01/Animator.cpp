#include "Animator.h"

#include "Engine.h"

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

void Animator::PlayFullAnimation(const std::string& type)
{
	for (AnimRecord* rec : m_animRecords)
	{
		if (type == rec->animation->getName())
		{
			rec->curTick = 0;
			rec->curFrame = 0;
			m_animFrame = 0;
			m_lastFrameTime = 0;
			return;
		}
	}
	
	m_animRecords.push_back(new AnimRecord(m_animationsMap[type]));
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
			for (AnimRecord* rec : m_animRecords)
			{
				if (m_nextAnimation == rec->animation->getName())
				{
					m_animFrame = rec->curFrame;
					m_lastFrameTime = rec->curTick;
				}
			}
		}
		//std::cout << SDL_GetTicks() - lastFrameTime << " vs " << anim->getFramesFrequency() << "\n";
		if (Engine::Instance().GetFrames() - m_lastFrameTime >= anim->GetFramesFrequency())
		{
			m_lastFrameTime = Engine::Instance().GetFrames();
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
	m_animationsMap[key]->setName(key);
}

void Animator::Update()
{
	Animation* nextAnim = m_animationsMap[m_nextAnimation];
	for (AnimRecord* rec : m_animRecords)
	{
		if ((nextAnim == nullptr) or (rec->animation->GetPriotity() >= nextAnim->GetPriotity()))
		{
			m_nextAnimation = rec->animation->getName();
		}
	}

	PlayAnimation();

	for (auto animRec = m_animRecords.begin(); animRec != m_animRecords.end();)
	{
		bool moved = false;
		if (Engine::Instance().GetFrames() - (*animRec)->curTick >= (*animRec)->animation->GetFramesFrequency())
		{
			(*animRec)->curTick = Engine::Instance().GetFrames();
			if (++(*animRec)->curFrame >= (*animRec)->animation->GetMaxFrames())
			{
				delete* animRec;
				animRec = m_animRecords.erase(animRec);
				moved = true;
			}
		}
		if (not moved)
		{
			animRec++;
		}
	}
}

void Animator::Clean()
{
	for (auto animPare : m_animationsMap)
	{
		delete animPare.second;
	}
}

bool Animator::AnimationIsPlaying(const std::string& key)
{
	bool foundInAnimRecords = false;
	for (AnimRecord* rec : m_animRecords)
	{
		if (key == rec->animation->getName())
		{
			foundInAnimRecords = true;
			break;
		}
	}
	
	return m_nextAnimation == key or foundInAnimRecords;
}

Animation* Animator::GetAnimation(const std::string& key)
{
	return m_animationsMap[key];
}

AnimRecord::AnimRecord(Animation* animation)
{
	this->animation = animation;
	this->curFrame = 0;
}

Animation::Animation(Uint32 maxFrames, Uint32 priority, Uint32 moveX, Uint32 moveY, Uint32 startX, Uint32 startY, Uint32 framesFrequency)
{
	this->m_startX = startX;
	this->m_startY = startY;
	this->m_maxFrames = maxFrames;
	this->m_moveX = moveX;
	this->m_moveY = moveY;
	this->m_priority = priority;
	this->m_framesFrequency = framesFrequency;
}
