#pragma once
#ifndef _COLLISIONMANAGER_H_
#define _COLLISIONMANAGER_H_

#include <iostream>
#include <SDL.h>

#include <vector>
#include "Entity.h"

class CollisionManager
{
public:
	static bool AABBCheck(const SDL_FRect& object1, const SDL_FRect& object2);

	static bool CircleCircleCheck(SDL_FPoint object1, SDL_FPoint object2, const double r1, const double r2 = 0.0);
	static bool CircleAABBCheck(const SDL_FPoint object1, const double r, const SDL_FRect& object2);

	static bool LinePointCheck(const SDL_FPoint object1_start, const SDL_FPoint object1_end, const SDL_FPoint object2);

	static bool PointRectCheck(const SDL_FPoint point, const SDL_FRect& object1);

	static bool LineLineCheck(SDL_FPoint line1_start, SDL_FPoint line1_end, SDL_FPoint line2_start, SDL_FPoint line2_end);
	static bool LineRectCheck(const SDL_FPoint& line1_start, const SDL_FPoint& line1_end, const SDL_FRect* box);
	
	static bool LOSCheck(SDL_FPoint* from, SDL_FPoint* to);
	static bool TunnelLOSCheck(SDL_FPoint* from, SDL_FPoint* to, int width);

	static GameObject* FindFirstObjectOnTheRay(SDL_FPoint Pos, SDL_FPoint Move, float maxDist = 9e3);
	static PathNode* GetClosestToPointNode(SDL_FPoint point, bool has_LOS = true, bool tunnel = false, Vec2 range = {0,9999});
	static PathNode* GetClosestTunnelNode(SDL_FPoint point);
	static float SquareRectDistance(const SDL_FRect& object1, const SDL_FRect& object2);
	static void CheckMapCollision(Entity* obj);
	static void CheckPhysicalCollision(SDL_FRect* rectObst, Entity* entity);

private:
	CollisionManager() {}
};

typedef CollisionManager COMA;

#endif