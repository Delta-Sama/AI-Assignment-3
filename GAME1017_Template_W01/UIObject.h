#pragma once
#ifndef _UIOBJECT_H_
#define _UIOBJECT_H_

#include"Sprite.h"

#include <string>

enum Priority { LOW, MEDIUM, HIGH };

class UIObject :public Sprite
{
public:
	UIObject(SDL_Rect s, SDL_FRect d, SDL_Texture* t, Priority priority) : Sprite(s, d, t), m_priority(priority)
	{
		m_enabled = true;
		m_active = true;
	}
	
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;
	
	void SetEnabled(bool enabled) { m_enabled = enabled; }
	void SetActive(bool active) { m_active = active; }
	
	bool GetActive() { return m_active; }
	SDL_Texture* GetTexture() { return m_pText; }
	Priority GetPriority() { return m_priority; }

protected:
	bool m_enabled,
		m_active;
	std::string UIType;

	Priority m_priority;
};


#endif