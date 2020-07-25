#pragma once
#ifndef _HEALTHBAR_H_
#define _HEALTHBAR_H_

#include "Label.h"
#include "UIObject.h"
#include "Entity.h"

class HealthBar final : public UIObject
{
public:
	HealthBar(Entity* entity);

	virtual void Update() override;
	virtual void Render() override;
	virtual void Clean() override;
	
private:
	Sprite* m_scale;
	Entity* m_entity;
};

#endif