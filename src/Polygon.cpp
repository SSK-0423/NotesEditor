#include "Polygon.hpp"
#include "Polygon.hpp"
#include "Point.hpp"
#include "DxLib.h"

Engine::PrimitiveObj::Polygon::Polygon() : color(GetColor(255, 255, 255))
{
}

Engine::PrimitiveObj::Polygon::Polygon(const Polygon& polygon) : color(GetColor(255,255,255))
{
	// vectorに値をコピー
	for (Point* p : polygon.vertex)
	{
		// pの値を使ってPointを作成し、それを自分のvertexに追加
		this->vertex.push_back(new Point(p->x,p->y));
	}
}

Engine::PrimitiveObj::Polygon::~Polygon()
{
	for (auto& p : vertex) 
	{
		delete p;
	}
	vertex.clear();
	vertex.shrink_to_fit();
}

void Engine::PrimitiveObj::Polygon::Draw()
{
	for (size_t i = 0; i < vertex.size() - 1; i++)
		DrawLineAA(vertex[i]->x, vertex[i]->y, vertex[i + 1]->x, vertex[i + 1]->y,color, 1.f);

	// 始点と終点を結ぶ
	DrawLineAA(vertex[vertex.size() - 1]->x, vertex[vertex.size() - 1]->y, vertex[0]->x, vertex[0]->y, color, 1.f);
}

void Engine::PrimitiveObj::Polygon::AddPoint(float x, float y)
{
	vertex.push_back(new Point(x, y));
}

void Engine::PrimitiveObj::Polygon::ChangedColor(int r, int g, int b)
{
	color = GetColor(r, g, b);
}

std::vector<Engine::PrimitiveObj::Point> Engine::PrimitiveObj::Polygon::GetVertexList() const
{
	std::vector<Point> points;

	for (auto p : vertex)
	{ 
		points.push_back(*p);
	}
	
	return points;
}

void Engine::PrimitiveObj::Polygon::ResetVertex()
{
	for (auto& p : vertex)
	{
		delete p;
	}
	vertex.clear();
	vertex.shrink_to_fit();
}