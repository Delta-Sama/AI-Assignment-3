#pragma once
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

struct Vec2
{
	Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	Vec2()
	{
		this->x = 0;
		this->y = 0;
	}
	float x;
	float y;
};

struct Vec4
{
	Vec4(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	Vec4()
	{
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->a = 0;
	}
	float r;
	float g;
	float b;
	float a;
};

#endif