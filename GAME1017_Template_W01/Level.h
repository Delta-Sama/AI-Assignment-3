#pragma once
#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <map>

#include "Tile.h"

class Level
{
public:
	Level() {};
	~Level() {};

	virtual void Load() = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;

private:

protected:
	std::map<char, Tile*> m_tiles;
};

#endif