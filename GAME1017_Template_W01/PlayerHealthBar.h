#pragma once
#ifndef _PLAYERHEALTHBAR_H_
#define _PLAYERHEALTHBAR_H_

#include "HealthBar.h"
#include "Entity.h"

class PlayerHealthBar final : public HealthBar
{
public:
	PlayerHealthBar(Entity* player);

	virtual void Update() override;
	
private:
	
};

#endif
