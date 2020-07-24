#pragma once
#ifndef _LEVEL1_H_
#define _LEVEL1_H_

#include "Level.h"

#include <array>

#define ROWS 24
#define COLS 32

class Level1 : public Level
{
public:
	virtual void Load() override;
	virtual void Render() override;
	virtual void Clean() override;
	
private:
	std::array<std::array<Tile*, COLS>, ROWS> m_level;
};

#endif
