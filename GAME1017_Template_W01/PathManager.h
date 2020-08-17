#pragma once
#ifndef _PATHMANAGER_H_
#define _PATHMANAGER_H_
#include "Pathing.h"
#include <vector>

class PathManager
{
public:
	static void Clear();
	static void Update();
	
	static PathNode* CreateNode(float x, float y);
	static void RecalculateConnections();
	static std::vector<PathConnection*> GetShortestPath(PathNode* start, PathNode* goal, bool reverse = false);
	
	static NodeRecord* GetSmallestNode(std::vector<NodeRecord*>* node_records);
	static bool ContainsNode(std::vector<NodeRecord*>& list, PathNode* n);
	static NodeRecord* GetNodeRecord(std::vector<NodeRecord*>& list, PathNode* n);
	static double HEuclid(PathNode* start, PathNode* goal);
	static double HManhat(const PathNode* start, const PathNode* goal);

	static double GetTotalPathCost(std::vector<PathConnection*>* s_path);
	static std::vector<PathNode*>* GetNodes() { return &s_nodes; }
	
private:
	PathManager() {}
private:

	static std::vector<PathNode*> s_nodes;
};

typedef PathManager PAMA;

#endif