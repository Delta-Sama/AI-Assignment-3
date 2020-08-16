#pragma once
#ifndef _LOCALPATHMANAGER_H_
#define _LOCALPATHMANAGER_H_

#include "Config.h"
#include "Pathing.h"

struct LocalPathManager
{
	LocalPathManager()
	{
		for (int i = 0; i < PREV_NODES_SIZE; i++)
		{
			prevNode[i] = nullptr;
		}
		prevCheck = 0;
		goalCounter = 0;
	}
	void CleanNodes()
	{
		for (int i = 0; i < PREV_NODES_SIZE; i++)
		{
			prevNode[i] = nullptr;
		}
	}
	PathNode* prevNode[PREV_NODES_SIZE];
	int prevCheck;
	int goalCounter;
};

#endif