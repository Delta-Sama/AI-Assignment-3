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

	// Update the object
	virtual void update() = 0;

	// remove anything that needs to be deleted
	virtual void clean() = 0;

	GameObjectType GetType() const;
	void SetType(GameObjectType new_type);

protected:
	GameObjectType m_type;
};

#endif