#pragma once
#ifndef _UIOBJECT_H_
#define _UIOBJECT_H_

#include"Sprite.h"

#include <string>

enum Priority { LOW, MEDIUM, HIGH };

class UIObject :public Sprite
{
public:
	UIObject(SDL_Rect s, SDL_FRect d, SDL_Texture* t, Priority priority, std::string name) : Sprite(s, d, t), m_priority(priority)
	{
		m_enabled = true;
		m_active = true;
		m_name = name;
	}
	
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;
	
	void SetEnabled(bool enabled) { m_enabled = enabled; }
	void SetActive(bool active) { m_active = active; }
	
	bool GetActive() { return m_active; }
	SDL_Texture* GetTexture() { return m_pText; }
	Priority GetPriority() { return m_priority; }

	std::string GetName() { return m_name; }

protected:
	bool m_enabled,
		m_active;
	std::string m_name;

	Priority m_priority;
};


#endif