#pragma once
#ifndef __UTIL__
#define __UTIL__

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
	static float distance(Vec2 vecA, Vec2 vecB);
	static float squaredDistance(Vec2 vecA, Vec2 vecB);
	static float magnitude(Vec2 vec);
	static float squaredMagnitude(Vec2 vec);
	static Vec2 limitMagnitude(Vec2 vector, float magnitude);
	static float lerp(float a, float b, float t);
	static float lerpUnclamped(float a, float b, float t);
	static float lerpAngle(float a, float b, float t);
	static float repeat(float t, float length);
	static float RandomRange(float min, float max);
	static float Sanitize(float value);
	static Vec2 min(Vec2 vecA, Vec2 vecB);
	static float min(float a, float b);
	static Vec2 max(Vec2 vecA, Vec2 vecB);
	static float max(float a, float b);
	static Vec2 negate(Vec2 vec);
	static Vec2 inverse(Vec2 vec);
	static Vec2 normalize(Vec2 vec);
	static float angle(Vec2 from, Vec2 to);
	static float dot(Vec2 lhs, Vec2 rhs);
	static float signedAngle(Vec2 from, Vec2 to);

	// debugging convenience functions
	static void DrawLine(Vec2 start, Vec2 end, Vec4 colour = Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	static void DrawRect(Vec2 position, int width, int height, Vec4 colour = Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	static void DrawCircle(Vec2 centre, int radius, Vec4 colour = Vec4(0.0f, 1.0f, 0.0f, 1.0f), ShapeType type = SYMMETRICAL);
	static void DrawCapsule(Vec2 position, int width, int height, Vec4 colour = Vec4(0.0f, 1.0f, 0.0f, 1.0f));
};

#endif /* defined (__UTIL__) */