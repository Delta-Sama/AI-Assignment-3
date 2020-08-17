#pragma once
#ifndef _HEALTHBAR_H_
#define _HEALTHBAR_H_

#include "Label.h"
#include "UIObject.h"
#include "Obstacle.h"

class ObjectHealthBar : public UIObject
{
public:
	ObjectHealthBar(Obstacle* obstacle);

	virtual void Update() override;
	virtual void Render() override;
	virtual void Clean() override;

protected:
	Sprite* m_scale;
	Obstacle* m_obstacle;
};

#endif