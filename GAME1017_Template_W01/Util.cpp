#include "Util.h"
#include "Engine.h"

#include <algorithm>
#include <math.h>
#include <SDL.h>

const float Util::Deg2Rad = M_PI / 180.0f;
const float Util::Rad2Deg = 180.0f / M_PI;
const float Util::EPSILON = 0.0001;

Util::Util()
= default;


Util::~Util()
= default;

/**
* Returns -1.0 if the value is less than 0 and 1.0 if the value is greater than 0
*/
float Util::sign(const float value)
{
	return (value < 0.0f) ? -1.0f : 1.0f;
}

/**
* This method confines the value provided between min and max and returns the result
*
*/
float Util::clamp(float value, const float min, const float max)
{
	if (value < min) {
		value = min;
	}
	else if (value > max) {
		value = max;
	}
	return value;
}

/**
* Clamps a value between 0 and 1 and returns the result
*
*/
float Util::clamp01(const float value)
{
	auto result = 0.0f;
	if (value < 0.0f) {
		result = 0.0f;
	}
	else if (value > 1.0f) {
		result = 1.0f;
	}
	else {
		result = value;
	}
	return result;
}

/**
* Returns the Euclidean distance of vecA and vecB
*/
float Util::distance(const SDL_FPoint vecA, const SDL_FPoint vecB)
{
	const auto x = vecB.x - vecA.x;
	const auto y = vecB.y - vecA.y;
	return sqrt((x * x) + (y * y));
}

/**
* Returns the Squared Euclidean distance of vecA and vecB
* No Square Root
*/
float Util::squaredDistance(const SDL_FPoint vecA, const SDL_FPoint vecB)
{
	const auto x = vecB.x - vecA.x;
	const auto y = vecB.y - vecA.y;
	return (x * x) + (y * y);
}

/**
* Returns the magnitude of a SDL_FPoint
*
*/
float Util::magnitude(const SDL_FPoint vec)
{
	const auto x = vec.x;
	const auto y = vec.y;
	return sqrt((x * x) + (y * y));
}

/**
* Returns the squared Magnitude of a SDL_FPoint
* No Square Root
*/
float Util::squaredMagnitude(SDL_FPoint vec)
{
	const auto x = vec.x;
	const auto y = vec.y;
	return (x * x) + (y * y);
}

/**
 * @brief
 *
 * @param vector
 * @param magnitude
 * @return SDL_FPoint
 */
SDL_FPoint Util::limitMagnitude(SDL_FPoint vector, const float magnitude)
{
	const auto length = Util::magnitude(vector);

	if (length > magnitude) {
		const auto limiter = magnitude / length;
		vector.x *= limiter;
		vector.y *= limiter;
		return vector;
	}
	else {
		return vector;
	}
}

/**
* Performs Linear Interpolation between and b
* at some t value between 0 and 1
*
*/
float Util::lerp(const float a, const float b, const float t)
{
	return a + (b - a) * Util::clamp01(t);
}

/**
	 * Lerps between a and b at some t value - unclamped.
*
*/
float Util::lerpUnclamped(const float a, const float b, const float t)
{
	return a + (b - a) * t;
}

/**
* Same as Lerp but makes sure the values interpolate correctly when they wrap around 360 degrees.
*
*/
float Util::lerpAngle(const float a, const float b, const float t)
{
	auto num = Util::repeat(b - a, 360.0);
	if (num > 180.0f) {
		num -= 360.0f;
	}
	return a + num * Util::clamp01(t);
}

/**
* Loops the value t, so that it is never larger than length and never smaller than 0.
*
*/

float Util::repeat(float t, float length)
{
	return Util::clamp(t - int(t / length) * length, 0.0f, length);
}

float Util::RandomRange(const float min, const float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

/**
* This Utility function checks to see if a number is very small (close to EPSILON)
* If so, it changes the value to 0.0;
*/
float Util::Sanitize(float value)
{
	if ((value >= -Util::EPSILON) && (value <= Util::EPSILON)) {
		value = 0.0;
	}
	return value;
}

/**
* This method computes the minimum values for x and y from vecA and vecB
* and returns them in dest or returns the result in a new SDL_FPoint
*
*/
SDL_FPoint Util::min(const SDL_FPoint vecA, const SDL_FPoint vecB)
{
	SDL_FPoint dest;
	dest.x = std::min(vecA.x, vecB.x);
	dest.y = std::min(vecA.y, vecB.y);
	return dest;
}

float Util::min(float a, float b)
{
	return a < b ? a : b;
}

/**
* This method computes the maximum values of x and y from vecA and vecB
* and returns the result in dest or returns the result as a new SDL_FPoint
*
*/
SDL_FPoint Util::max(const SDL_FPoint vecA, const SDL_FPoint vecB)
{
	SDL_FPoint  dest;
	dest.x = std::max(vecA.x, vecB.x);
	dest.y = std::max(vecA.y, vecB.y);
	return dest;
}

float Util::max(float a, float b)
{
	return a > b ? a : b;
}

/**
* Negates the x and y components of a SDL_FPoint and returns them in a new SDL_FPoint object
*
*/
SDL_FPoint Util::negate(const SDL_FPoint vec)
{
	SDL_FPoint dest;
	dest.x = -vec.x;
	dest.y = -vec.y;
	return dest;
}

/**
* Returns the inverse x and y components of src SDL_FPoint and returns them in a new SDL_FPoint object
*
*/
SDL_FPoint Util::inverse(const SDL_FPoint vec)
{
	SDL_FPoint dest;
	dest.x = 1.0 / vec.x;
	dest.y = 1.0 / vec.y;
	return dest;
}


/**
* Normalizes SDL_FPoint and stores the result in a new SDL_FPoint object
*
*/
SDL_FPoint Util::normalize(const SDL_FPoint vec)
{
	SDL_FPoint dest;
	auto x = vec.x;
	auto y = vec.y;
	auto length = (x * x) + (y * y);
	if (length > 0) {
		length = 1.0 / sqrt(length);
		dest.x = vec.x * length;
		dest.y = vec.y * length;
	}
	return dest;
}

/**
* Returns the angle in degrees between from and to.
*/
float Util::angle(const SDL_FPoint from, const SDL_FPoint to)
{
	return acos(Util::clamp(Util::dot(Util::normalize(from), Util::normalize(to)), -1.0f, 1.0f)) * 57.29578f;
}

/**
* Dot Product of two vectors.
*/
float Util::dot(const SDL_FPoint lhs, const SDL_FPoint rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Util::signedAngle(const SDL_FPoint from, const SDL_FPoint to)
{
	const auto unsigned_angle = Util::angle(from, to);
	const auto sign = Util::sign(from.x * to.y - from.y * to.x);
	return unsigned_angle * sign;
}

void Util::DrawLine(SDL_FPoint start, SDL_FPoint end, Vec4 colour)
{
	int r = floor(colour.r * 255.0f);
	int g = floor(colour.g * 255.0f);
	int b = floor(colour.b * 255.0f);
	int a = floor(colour.a * 255.0f);

	SDL_Renderer* renderer = Engine::Instance().GetRenderer();

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Util::DrawRect(SDL_FPoint position, int width, int height, Vec4 colour)
{
	int r = floor(colour.r * 255.0f);
	int g = floor(colour.g * 255.0f);
	int b = floor(colour.b * 255.0f);
	int a = floor(colour.a * 255.0f);

	SDL_Rect rectangle;
	rectangle.x = position.x;
	rectangle.y = position.y;
	rectangle.w = width;
	rectangle.h = height;

	SDL_Renderer* renderer = Engine::Instance().GetRenderer();

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawRect(renderer, &rectangle);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Util::DrawCircle(SDL_FPoint centre, int radius, Vec4 colour, ShapeType type)
{
	int r = floor(colour.r * 255.0f);
	int g = floor(colour.g * 255.0f);
	int b = floor(colour.b * 255.0f);
	int a = floor(colour.a * 255.0f);

	SDL_Renderer* renderer = Engine::Instance().GetRenderer();

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	int diameter = floor(radius * 2.0f);

	int x = (radius - 1);
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = (tx - diameter);

	while (x >= y)
	{
		switch (type)
		{
		case SEMI_CIRCLE_TOP:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y - x);
			break;
		case SEMI_CIRCLE_BOTTOM:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y + y); // bottom right
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y + y); // bottom left
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y + x); // bottom right
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y + x); // bottom left
			break;
		case SEMI_CIRCLE_LEFT:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y + y);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y + x);
			break;
		case SEMI_CIRCLE_RIGHT:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y + y);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y + x);
			break;
		case SYMMETRICAL:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y + y);
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y + y);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y + x);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y + x);
			break;
		}


		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Util::DrawCapsule(SDL_FPoint position, int width, int height, Vec4 colour)
{
	int diameter;
	int radius;
	int halfWidth = floor(width * 0.5f);
	int halfHeight = floor(height * 0.5f);
	if (width > height)
	{
		// Horizontal Capsule
		diameter = height;
		radius = halfHeight * 0.5f;
		DrawCircle({ position.x - halfWidth + halfHeight, position.y }, halfHeight, colour, SEMI_CIRCLE_LEFT);
		DrawCircle({ position.x + halfWidth - halfHeight, position.y }, halfHeight, colour, SEMI_CIRCLE_RIGHT);
		DrawLine({ position.x - halfWidth + halfHeight, position.y - halfHeight }, { position.x + halfWidth - halfHeight, position.y - halfHeight });
		DrawLine({ position.x - halfWidth + halfHeight, position.y + halfHeight }, { position.x + halfWidth - halfHeight, position.y + halfHeight });
	}
	else if (width < height)
	{
		// Vertical Capsule
		diameter = width;
		radius = halfWidth * 0.5f;
		DrawCircle({ position.x, position.y - halfHeight + radius }, radius, colour, SEMI_CIRCLE_TOP);
		DrawCircle({ position.x, position.y + halfHeight - radius }, radius, colour, SEMI_CIRCLE_BOTTOM);
		DrawLine({ position.x - radius, position.y - halfHeight + radius }, { position.x - halfWidth * 0.5f, position.y + halfHeight * 0.5f });
		DrawLine({ position.x + radius, position.y - halfHeight + radius }, { position.x + halfWidth * 0.5f, position.y + halfHeight * 0.5f });
	}
	else
	{
		// Circle
		diameter = floor(height * 2.0f);
		radius = width;
		DrawCircle(position, radius = halfWidth, colour);
	}
}