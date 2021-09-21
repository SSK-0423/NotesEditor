#pragma once
#include <math.h>

namespace Game
{
	namespace Object
	{
		namespace Polygon
		{
			struct Point {
				float x, y;

				Point() : x(0.f), y(0.f) {}
				Point(float x, float y) : x(x), y(y) {}

				Point operator+(const Point& p) const
				{
					Point point;
					point.x = this->x + p.x;
					point.y = this->y + p.y;
					return point;
				}
				Point operator-(const Point& p) const
				{
					Point point;
					point.x = this->x - p.x;
					point.y = this->y - p.y;
					return point;
				}
				
				// �萔�{
				friend Point operator*(float num, const Point& p)
				{
					Point point;
					point.x = num * p.x;
					point.y = num * p.y;
					return point;
				}

				// ����Z
				friend Point operator/(float num, const Point& p)
				{
					Point point;
					point.x = p.x / num;
					point.y = p.y / num;
					return point;
				}

				// ����
				float Dot(const Point& p) const
				{
					return this->x * p.x + this->y * p.y;
				}
				
				// �O��
				float Cross(const Point& p) const
				{
					return this->x * p.y - this->y * p.x;
				}
				
				// ��Βl��2��
				float AbsNoSquare() 
				{
					return this->x * this->x + this->y * this->y;
				}

				// ��Βl
				float Abs()
				{
					return sqrtf(AbsNoSquare());
				}

				void SetPoint(float x, float y) 
				{
					this->x = x;
					this->y = y;
				}
			};
		}
	}
}