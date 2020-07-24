#include "GameObject.h"

GameObject::GameObject(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : Sprite(s, d, t), m_type(NONE)
{
}

GameObject::~GameObject()
= default;

GameObjectType GameObject::getType() const
{
	return m_type;
}

void GameObject::setType(const GameObjectType new_type)
{
	m_type = new_type;
}
