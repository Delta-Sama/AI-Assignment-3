#include "MathManager.h"

double MathManager::Distance(const double& x1, const double& x2, const double& y1, const double& y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double MathManager::SquareDistance(SDL_FPoint* from, SDL_FPoint* to)
{
	return (to->x - from->x) * (to->x - from->x) + (to->y - from->y) * (to->y - from->y);
}

double MathManager::AngleBetweenPoints(const double dy, const double dx)
{
	return atan2(dy, dx); // In radians.
}

void MathManager::SetDeltas(const double angle, double& dx, double &dy, double fx, double fy)
{
	dx = SetDeltaX(angle, fx);
	dy = SetDeltaY(angle, fy);
}

double MathManager::SetDeltaX(const double angle, double fx)
{
	return cos(angle) * fx;
}

double MathManager::SetDeltaY(const double angle, double fy)
{
	return sin(angle) * fy;
}

double MathManager::Deg2Rad(const double angle)
{
	return angle * M_PI / 180.0;
}

double MathManager::Rad2Deg(const double angle)
{
	return angle * 180.0 / M_PI;
}

SDL_Rect MathManager::ConvertFRect2Rect(const SDL_FRect& r)
{
	SDL_Rect temp = { (int)r.x, (int)r.y, (int)r.w, (int)r.h };
	return temp;
}

SDL_Point MathManager::HalfwayPoint(const SDL_Point& from, const SDL_Point& to)
{
	return { (int)(((double)from.x + (double)to.x) / 2.0), (int)(((double)from.y + (double)to.y) / 2.0) };
}

double MathManager::Angle180(double a)
{
	a = fmod(a + 180.0, 360.0);
	if (a < 0)
		a += 360.0;
	return a - 180.0;
}
