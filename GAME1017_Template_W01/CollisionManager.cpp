#include "CollisionManager.h"
#include "DebugManager.h"
#include "EnemyManager.h"
#include "Engine.h"
#include "GameObjectManager.h"
#include "MathManager.h"
#include "PathManager.h"
#include "StateManager.h"
#include "Tile.h"
#include "Util.h"

bool CollisionManager::AABBCheck(const SDL_FRect& object1, const SDL_FRect& object2)
{
	return (object1.x < object2.x + object2.w and
		object1.x + object1.w > object2.x and
		object1.y < object2.y + object2.h and
		object1.y + object1.h > object2.y);
}

bool CollisionManager::CircleCircleCheck(SDL_FPoint object1, SDL_FPoint object2, const double r1, const double r2)
{
	return (MAMA::Distance(object1, object2) < (r1 + r2));
}

bool CollisionManager::CircleAABBCheck(const SDL_FPoint object1, const double r, const SDL_FRect& object2)
{
	double x1 = (double)object1.x;
	double y1 = (double)object1.y;
	if (object1.x < object2.x) // Circle center, rect left edge.
		x1 = (double)object2.x;
	else if (object1.x > object2.x + object2.w)
		x1 = (double)object2.x + (double)object2.w;
	if (object1.y < object2.y)
		y1 = (double)object2.y;
	else if (object1.y > object2.y + object2.h)
		y1 = (double)object2.y + (double)object2.h;

	return CircleCircleCheck({ (float)x1, (float)y1 }, { (float)object1.x, (float)object1.y }, r);
}

bool CollisionManager::LinePointCheck(SDL_FPoint object1_start, SDL_FPoint object1_end, SDL_FPoint object2)
{
	double distToStart = MAMA::Distance(object1_start, object2);
	double distToEnd = MAMA::Distance(object1_end, object2);

	double lineLength = MAMA::Distance(object1_start, object1_end);

	double buffer = 0.2; // Extra distance since line thickness is one pixel.

	if (distToStart + distToEnd <= lineLength + buffer)
		return true;
	return false;
}

bool CollisionManager::PointRectCheck(const SDL_FPoint point, const SDL_FRect& object1)
{
	return (point.x <= object1.x + object1.w and
		point.x >= object1.x and
		point.y <= object1.y + object1.h and
		point.y >= object1.y);
}

GameObject* CollisionManager::FindFirstObjectOnTheRay(SDL_FPoint Pos, SDL_FPoint Move, float maxDist)
{
	float len = sqrt(Move.x * Move.x + Move.y * Move.y);
	float dx = Move.x / len;
	float dy = Move.y / len;

	float dist = 0;
	bool distancing = false;
	if (maxDist < 9e3)
	{
		maxDist *= maxDist;
		distancing = true;
	}

	SDL_FPoint curPos = { Pos.x, Pos.y };

	int sizeX, sizeY;
	SDL_GetWindowSize(Engine::Instance().GetWindow(), &sizeX, &sizeY);
	
	while (curPos.x > 0 and curPos.x < (float)sizeX and curPos.y > 0 and curPos.y < (float)sizeY and dist < maxDist)
	{
		curPos.x += dx;
		curPos.y += dy;
		if (distancing)
		{
			dist += dx * dx + dy * dy;
		}
		for (GameObject* obj : *GameObjectManager::GetObjects())
		{
			if (COMA::PointRectCheck(curPos, *obj->GetDstP()))//entity->getCanCollide() and
			{
				return obj;
			}
		}
	}
	return nullptr;
}

PathNode* CollisionManager::GetClosestToPointNode(SDL_FPoint point, bool has_LOS, bool tunnel, Vec2 range)
{
	PathNode* LOS_node = nullptr;
	long min_dist = 99999;

	for (PathNode* node : *PAMA::GetNodes())
	{
		SDL_FPoint temp_pos = { node->x, node->y };

		long dist = (long int)MAMA::SquareDistance(&ENMA::GetPlayer()->GetCenter(), &temp_pos);

		bool in_range = (dist >= pow(range.x,2) and dist <= pow(range.y, 2));
		
		if (in_range and dist < min_dist)
		{
			bool player_LOS = not tunnel and node->GetPlayerLOS() == has_LOS;
			bool tunnel_LOS = tunnel and COMA::TunnelLOSCheck(&ENMA::GetPlayer()->GetCenter(), &temp_pos, TUNNEL_ENTITY_WIDTH);

			if (player_LOS or tunnel_LOS)
			{
				min_dist = dist;
				LOS_node = node;
			}
		}
	}

	return LOS_node;
}

PathNode* CollisionManager::GetClosestTunnelNode(SDL_FPoint point)
{
	PathNode* LOS_node = nullptr;
	long min_dist = 99999;

	for (PathNode* node : *PAMA::GetNodes())
	{
		SDL_FPoint temp_pos = { node->x, node->y };
		if (COMA::TunnelLOSCheck(&temp_pos, &point, TUNNEL_ENTITY_WIDTH))
		{
			long dist = (long)MAMA::SquareDistance(&point, &temp_pos);

			if (dist < min_dist)
			{
				min_dist = dist;
				LOS_node = node;
			}
		}
	}

	return LOS_node;
}

bool CollisionManager::LineLineCheck(SDL_FPoint line1_start, SDL_FPoint line1_end, SDL_FPoint line2_start, SDL_FPoint line2_end)
{
	const auto x1 = line1_start.x;
	const auto x2 = line1_end.x;
	const auto x3 = line2_start.x;
	const auto x4 = line2_end.x;
	const auto y1 = line1_start.y;
	const auto y2 = line1_end.y;
	const auto y3 = line2_start.y;
	const auto y4 = line2_end.y;

	// calculate the distance to intersection point
	const auto uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	const auto uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		return true;
	}

	return false;
}

bool CollisionManager::LineRectCheck(const SDL_FPoint& line1_start, const SDL_FPoint& line1_end, const SDL_FRect* box)
{
	const auto x1 = line1_start.x;
	const auto x2 = line1_end.x;
	const auto y1 = line1_start.y;
	const auto y2 = line1_end.y;
	const auto rx = box->x;
	const auto ry = box->y;
	const auto rw = box->w;
	const auto rh = box->h;

	// check if the line has hit any of the rectangle's sides
	// uses the Line/Line function below
	const bool left = LineLineCheck({x1, y1}, {x2, y2}, {rx, ry}, {rx, ry + rh});
	const bool right = LineLineCheck({ x1, y1 }, { x2, y2 }, { rx + rw, ry }, { rx + rw, ry + rh });
	const bool top = LineLineCheck({ x1, y1 }, { x2, y2 }, { rx, ry }, { rx + rw, ry });
	const bool bottom = LineLineCheck({ x1, y1 }, { x2, y2 }, { rx, ry + rh }, { rx + rw, ry + rh });

	// if ANY of the above are true, the line
	// has hit the rectangle
	if (left || right || top || bottom) {
		return true;
	}

	return false;
}

bool CollisionManager::LOSCheck(SDL_FPoint* from, SDL_FPoint* to)
{
	for (Tile* tile : *GameObjectManager::GetCollidableTiles())
	{
		const SDL_FRect* box = tile->GetDstP();

		if (LineRectCheck(*from, *to, box))
		{
			return false;
		}
	}

	for (Obstacle* obstacle : *GameObjectManager::GetObstacles())
	{
		const SDL_FRect* box = obstacle->GetDstP();

		if (LineRectCheck(*from, *to, box))
		{
			return false;
		}
	}
	
	return true;
}

bool CollisionManager::TunnelLOSCheck(SDL_FPoint* from, SDL_FPoint* to, int width)
{
	Vec2 init_line = { to->x - from->x, to->y - from->y };
	float perpX, perpY;
	
	// Calculate the unit perpendicular
	if (init_line.x != 0)
	{
		perpY = 1;
		perpX = -(init_line.y * perpY) / init_line.x;
	}
	else if (init_line.y != 0)
	{
		perpX = 1;
		perpY = -(init_line.x * perpX) / init_line.y;
	}
	else
	{
		return true;
	}
	float len = sqrt(pow(perpX, 2) + pow(perpY, 2));
	Vec2 perp = { perpX / len, perpY / len };

	SDL_FPoint right_line_from = { from->x + perp.x * width, from->y + perp.y * width };
	SDL_FPoint right_line_to = { to->x + perp.x * width, to->y + perp.y * width };

	SDL_FPoint left_line_from = { from->x - perp.x * width, from->y - perp.y * width };
	SDL_FPoint left_line_to = { to->x - perp.x * width, to->y - perp.y * width };

	/*Vec4 col = { 0,0,1,1 };
	Util::QueueLine(right_line_from, right_line_to, col);
	Util::QueueLine(left_line_from, left_line_to, col);*/
	
	for (Tile* tile : *GameObjectManager::GetCollidableTiles())
	{
		const SDL_FRect* box = tile->GetDstP();

		if (LineRectCheck(right_line_from, right_line_to, box)
			or LineRectCheck(left_line_from, left_line_to, box))
		{
			return false;
		}
	}

	for (Obstacle* obstacle : *GameObjectManager::GetObstacles())
	{
		const SDL_FRect* box = obstacle->GetDstP();

		if (LineRectCheck(right_line_from, right_line_to, box)
			or LineRectCheck(left_line_from, left_line_to, box))
		{
			return false;
		}
	}

	return true;
}

float CollisionManager::SquareRectDistance(const SDL_FRect& object1, const SDL_FRect& object2)
{
	float x1 = object1.x + object1.w / 2;
	float x2 = object2.x + object2.w / 2;
	float y1 = object1.y + object1.h / 2;
	float y2 = object2.y + object2.h / 2;
	return (pow(x1 - x2, 2.0f) + pow(y1 - y2, 2.0f));
}

void CollisionManager::CheckMapCollision(Entity* entity)
{
	for (Tile* tile : *GameObjectManager::GetCollidableTiles())
	{
		if (tile->IsObstacle())
		{
			CheckPhysicalCollision(tile->GetDstP(), entity);
		}
	}
	for (Obstacle* obst : *GameObjectManager::GetObstacles())
	{
		CheckPhysicalCollision(obst->GetDstP(), entity);
	}
}

void CollisionManager::CheckPhysicalCollision(SDL_FRect* obstRect, Entity* entity)
{
	SDL_FRect* entityRect = entity->GetBody();
	if (COMA::AABBCheck(*entityRect, *obstRect))
	{
		if (entityRect->y + entityRect->h - (float)entity->GetMoveEngine()->GetVelY() <= obstRect->y)
		{ // Colliding top side of platform.
			entity->GetMoveEngine()->StopY();
			entity->SetY(obstRect->y - entityRect->h);
		}
		else if (entityRect->y - (float)entity->GetMoveEngine()->GetVelY() >= obstRect->y + obstRect->h)
		{ // Colliding bottom side of platform.
			entity->GetMoveEngine()->StopY();
			entity->SetY(obstRect->y + obstRect->h);
		}
		else if (entityRect->x + entityRect->w - (float)entity->GetMoveEngine()->GetVelX() <= obstRect->x)
		{ // Collision from left.
			entity->GetMoveEngine()->StopX();
			entity->SetX(obstRect->x - entityRect->w);
		}
		else if (entityRect->x - (float)entity->GetMoveEngine()->GetVelX() >= obstRect->x + obstRect->w)
		{
			entity->GetMoveEngine()->StopX();
			entity->SetX(obstRect->x + obstRect->w);
		}
	}
}