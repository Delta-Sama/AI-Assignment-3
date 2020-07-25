#pragma once
#ifndef _LOCALPATHMANAGER_H_
#define _LOCALPATHMANAGER_H_

#include "Config.h"
#include "Pathing.h"

struct LocalPathManager
{
	LocalPathManager()
	{
		for (int i = 0; i < PREVNODESSIZE; i++)
		{
			prevNode[i] = nullptr;
		}
		prevCheck = 0;
		goalCounter = 0;
	}
	void CleanNodes()
	{
		for (int i = 0; i < PREVNODESSIZE; i++)
		{
			prevNode[i] = nullptr;
		}
	}
	PathNode* prevNode[PREVNODESSIZE];
	int prevCheck;
	int goalCounter;
};

#endif