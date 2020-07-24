#pragma once
#ifndef _UIOBJECT_H_
#define _UIOBJECT_H_

#include"Sprite.h"

#include <string>

class UIObject :public Sprite
{
public:
	UIObject(SDL_Rect s, SDL_FRect d, SDL_Texture* t) :Sprite(s, d, t)
	{
		isDisplay = true;
	}
	virtual void Update() = 0;
	virtual void Render() = 0;
	void setIsDisplay(bool a) { isDisplay = a; }
	void setIsActive(bool a) { isActive = a; }
	bool getActive() { return isActive; }
	SDL_Texture* getTexture() { return m_pText; }

protected:
	bool isDisplay,
		isActive;
	std::string UIType;
};


#endif