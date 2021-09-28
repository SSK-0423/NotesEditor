#pragma once
#include <math.h>

namespace PolygonObjectObject
{
	struct Point {
		float x, y;

		Point() : x(0.f), y(0.f) {}
		Point(float x, float y) : x(x), y(y) {}

		// ‰ÁZ
		Point operator+(const Point& p) const
		{
			Point point;
			point.x = this->x + p.x;
			point.y = this->y + p.y;
			return point;
		}

		// ‰ÁZ‘ã“ü
		Point& operator+=(const Point& p)
		{
			this->x += p.x;
			this->y += p.y;
			return *this;
		}

		// Œ¸Z
		Point operator-(const Point& p) const
		{
			Point point;
			point.x = this->x - p.x;
			point.y = this->y - p.y;
			return point;
		}

		// Œ¸Z‘ã“ü
		Point& operator-=(const Point& p)
		{
			this->x -= p.x;
			this->y -= p.y;
			return *this;
		}

		// ’è””{
		friend Point operator*(float num, const Point& p)
		{
			Point point;
			point.x = num * p.x;
			point.y = num * p.y;
			return point;
		}

		// Š„‚èZ
		friend Point operator/(float num, const Point& p)
		{
			Point point;
			point.x = p.x / num;
			point.y = p.y / num;
			return point;
		}

		// “àÏ
		float Dot(const Point& p) const
		{
			return this->x * p.x + this->y * p.y;
		}

		// ŠOÏ
		float Cross(const Point& p) const
		{
			return this->x * p.y - this->y * p.x;
		}

		// â‘Î’l‚Ì2æ
		float AbsNoSquare()
		{
			return this->x * this->x + this->y * this->y;
		}

		// â‘Î’l
		float Abs()
		{
			return sqrtf(AbsNoSquare());
		}
	};
}
