#pragma once
#ifndef __UTIL__
#define __UTIL__

#include <SDL_rect.h>

#include "Vector2.h"

enum ShapeType
{
	SEMI_CIRCLE_LEFT,
	SEMI_CIRCLE_RIGHT,
	SEMI_CIRCLE_TOP,
	SEMI_CIRCLE_BOTTOM,
	SYMMETRICAL
};

class Util
{
public:
	Util();
	~Util();

	static const float EPSILON;
	static const float Deg2Rad;
	static const float Rad2Deg;

	static float sign(float value);
	static float clamp(float value, float min, float max);
	static float clamp01(float value);
	static float distance(SDL_FPoint vecA, SDL_FPoint vecB);
	static float squaredDistance(SDL_FPoint vecA, SDL_FPoint vecB);
	static float magnitude(SDL_FPoint vec);
	static float squaredMagnitude(SDL_FPoint vec);
	static SDL_FPoint limitMagnitude(SDL_FPoint vector, float magnitude);
	static float lerp(float a, float b, float t);
	static float lerpUnclamped(float a, float b, float t);
	static float lerpAngle(float a, float b, float t);
	static float repeat(float t, float length);
	static float RandomRange(float min, float max);
	static float Sanitize(float value);
	static SDL_FPoint min(SDL_FPoint vecA, SDL_FPoint vecB);
	static float min(float a, float b);
	static SDL_FPoint max(SDL_FPoint vecA, SDL_FPoint vecB);
	static float max(float a, float b);
	static SDL_FPoint negate(SDL_FPoint vec);
	static SDL_FPoint inverse(SDL_FPoint vec);
	static SDL_FPoint normalize(SDL_FPoint vec);
	static float angle(SDL_FPoint from, SDL_FPoint to);
	static float dot(SDL_FPoint lhs, SDL_FPoint rhs);
	static float signedAngle(SDL_FPoint from, SDL_FPoint to);

	// debugging convenience functions
	static void DrawLine(SDL_FPoint start, SDL_FPoint end, Vec4 colour = Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	static void DrawRect(SDL_FPoint position, int width, int height, Vec4 colour = Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	static void DrawCircle(SDL_FPoint centre, int radius, Vec4 colour = Vec4(0.0f, 1.0f, 0.0f, 1.0f), ShapeType type = SYMMETRICAL);
	static void DrawCapsule(SDL_FPoint position, int width, int height, Vec4 colour = Vec4(0.0f, 1.0f, 0.0f, 1.0f));
};

#endif /* defined (__UTIL__) */