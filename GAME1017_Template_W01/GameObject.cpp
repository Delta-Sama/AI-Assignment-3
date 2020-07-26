#include "GameObject.h"

GameObject::GameObject(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : Sprite(s, d, t), m_type(NONE)
{
}

GameObject::~GameObject()
= default;

GameObjectType GameObject::GetType() const
{
	return m_type;
}

void GameObject::SetType(const GameObjectType new_type)
{
	m_type = new_type;
}
