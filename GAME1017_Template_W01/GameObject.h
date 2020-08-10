#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "GameObjectTypes.h"
#include "Sprite.h"
#include "Vector2.h"

class GameObject : public Sprite
{
public:
	GameObject(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual void Clean() = 0;

	GameObjectType GetType() const;
	void SetType(GameObjectType new_type);

protected:
	GameObjectType m_type;
};

#endif