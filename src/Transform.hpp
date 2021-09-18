#pragma once
#include "Game.hpp"

class Transform{
private:
	// 座標
	Position2D<float> position;
	// サイズ
	Size2D<float> size;
public:
	Position2D<float> GetPosition() const
	{
		return position;
	}
	float GetPosX() const
	{
		return position.x;
	}
	float GetPosY() const
	{
		return position.y;
	}

	Size2D<float> GetSize() const
	{
		return size;
	}
	float GetWidth() const
	{
		return size.width;
	}
	float GetHeight() const
	{
		return size.height;
	}

	void SetPosition(Position2D<float> pos) 
	{
		position = pos;
	}
	void SetSize(Size2D<float> s) {
		size = s;
	}
};