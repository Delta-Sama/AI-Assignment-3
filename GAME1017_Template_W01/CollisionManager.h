#pragma once
#ifndef _COLLISIONMANAGER_H_
#define _COLLISIONMANAGER_H_

#include <iostream>
#include <SDL.h>

#include <vector>
#include "GameObject.h"

class CollisionManager
{
public:
	static bool AABBCheck(const SDL_FRect& object1, const SDL_FRect& object2);

	static bool CircleCircleCheck(const SDL_FPoint object1, const SDL_FPoint object2, const double r1, const double r2 = 0.0);
	static bool CircleAABBCheck(const SDL_FPoint object1, const double r, const SDL_FRect& object2);

	static bool LinePointCheck(const SDL_FPoint object1_start, const SDL_FPoint object1_end, const SDL_FPoint object2);

	static bool PointRectCheck(const SDL_FPoint point, const SDL_FRect& object1);

	static bool LineLineCheck(Vec2 line1_start, Vec2 line1_end, Vec2 line2_start, Vec2 line2_end);
	static bool LineRectCheck(const SDL_FPoint& line1_start, const SDL_FPoint& line1_end, const SDL_FRect* box);
	
	static bool LOSCheck(GameObject* from, GameObject* to);
	static GameObject* FindFirstObjectOnTheRay(SDL_FPoint Pos, SDL_FPoint Move, float maxDist = 9e3);
	static float SquareRectDistance(const SDL_FRect& object1, const SDL_FRect& object2);
	static void CheckMapCollision(const std::vector<GameObject*> mapObjects, GameObject* obj);

private:
	CollisionManager() {}
};

typedef CollisionManager COMA;

#endif