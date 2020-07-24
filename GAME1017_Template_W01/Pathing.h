#pragma once
#ifndef _PATHING_H_
#define _PATHING_H_
#include <SDL.h>
#include <vector>

class PathConnection;

class PathNode : public SDL_Point
{
public:
	PathNode(int x, int y);
	~PathNode();
	void Update();
	void AddConnection(PathConnection* c);
	std::vector<PathConnection*>& GetConnections();
	SDL_Point Point() { return { x, y }; }
	double Heuristic() { return m_heur; }
	void SetHeuristic(double heur) { m_heur = heur; }
private:
	double m_heur; // Heuristic cost for node.
	std::vector<PathConnection*> m_connections;
};

class PathConnection
{
public:
	PathConnection(PathNode* from, PathNode* to, double cost = 1.0);
	~PathConnection() {}
	double GetCost() { return m_cost; }
	void SetCost(double cost) { m_cost = cost; }
	PathNode* GetFromNode() { return m_pFromNode; }
	PathNode* GetToNode() { return m_pToNode; }
private:
	double m_cost;
	PathNode* m_pFromNode, * m_pToNode;
};

struct NodeRecord
{
	NodeRecord(PathNode* n = nullptr) :m_node(n), m_connection(nullptr), m_fromRecord(nullptr), m_costSoFar(0.0), m_totalCost(0.0) {	}
	PathNode* m_node;
	PathConnection* m_connection;
	NodeRecord* m_fromRecord;
	double m_costSoFar;
	double m_totalCost;
};
#endif
