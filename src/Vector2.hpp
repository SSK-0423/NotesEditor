#pragma once

template<class T>
struct Vector2;

template<>
struct Vector2<int>
{
	int x;
	int y;
	Vector2() : x(0),y(0)
	{
	}
	Vector2(int x, int y) : x(x), y(y)
	{
	}
};

template<>
struct Vector2<float>
{
	float x;
	float y;
	Vector2() : x(0.f), y(0.f)
	{
	}
	Vector2(float x,float y) : x(x), y(y)
	{
	}
};