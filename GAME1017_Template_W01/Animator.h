#pragma once

#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include <string>
#include <map>
#include <iostream>
#include "Entity.h"

// Animation engine by Maxim Dobrivskiy

class Animation
{
public:
	Animation(Uint32 maxFrames, Uint32 priority, Uint32 moveX, Uint32 moveY = 0, Uint32 startX = 0, Uint32 startY = 0, Uint32 framesFrequency = 8);

	Uint32 GetMoveX() { return m_moveX; }
	Uint32 GetMoveY() { return m_moveY; }
	Uint32 GetStartX() { return m_startX; }
	Uint32 GetStartY() { return m_startY; }
	Uint32 GetPriotity() { return m_priority; }
	Uint32 GetMaxFrames() { return m_maxFrames; }
	Uint32 GetFramesFrequency() { return m_framesFrequency; }
	
private:
	Uint32 m_maxFrames;
	Uint32 m_moveX;
	Uint32 m_moveY;
	Uint32 m_startX;
	Uint32 m_startY;
	Uint32 m_priority;
	Uint32 m_framesFrequency;
	
};

class Animator
{
public:
	Animator(Entity* animEntity);
	
	void SetNextAnimation(const std::string& type);
	void PlayAnimation();//Plays the animation with the highest priority in the "hill"
	void AddAnimation(const std::string& key, Uint32 maxFrames, Uint32 priority, Uint32 moveX, Uint32 moveY = 0, Uint32 startX = 0, Uint32 startY = 0, Uint32 framesFrequency = 8);

	void Clean();
	
	Animation* GetAnimation(const std::string& key);

	std::map<std::string, Animation*> m_animationsMap;
	
private:
	Uint32 m_faceSide;
	Uint32 m_animFrame;
	Uint32 m_maxAnimationFrames;
	Uint32 m_curAnimationPriority;
	Uint32 m_lastFrameTime;
	std::string m_nextAnimation;
	Entity* m_entity;
	std::string m_curAnimType;
	
};

#endif