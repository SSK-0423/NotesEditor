#include "Polygon.hpp"
#include "Polygon.hpp"
#include "Point.hpp"
#include "DxLib.h"

Engine::PrimitiveObj::Polygon::Polygon() : color(GetColor(255, 255, 255))
{
}

Engine::PrimitiveObj::Polygon::Polygon(const Polygon& polygon) : color(GetColor(255, 255, 255))
{
	for (auto p : polygon.vertex)
	{
		this->vertex.push_back(new Point(p->x, p->y));
	}
}

Engine::PrimitiveObj::Polygon::~Polygon()
{
	ResetVertex();
}

void Engine::PrimitiveObj::Polygon::Draw()
{
	for (size_t i = 0; i < vertex.size() - 1; i++)
		DrawLineAA(vertex[i]->x, vertex[i]->y, vertex[i + 1]->x, vertex[i + 1]->y, color, 1.f);

	// 始点と終点を結ぶ
	DrawLineAA(vertex.back()->x, vertex.back()->y, vertex[0]->x, vertex[0]->y, color, 1.f);
}

void Engine::PrimitiveObj::Polygon::AddPoint(float x, float y)
{
	vertex.push_back(new Point(x, y));
}

void Engine::PrimitiveObj::Polygon::ChangedColor(Color color)
{
	this->color = color;
}

std::vector<Engine::PrimitiveObj::Point> Engine::PrimitiveObj::Polygon::GetVertexList() const
{
	// vertexをそのまま渡すと同じアドレスのリソースを使うことになるので、
	// vertexと同じ値で異なるアドレスのvectorを作成し、戻り値とする
	std::vector<Point> points;

	for (auto p : vertex)
		points.push_back(*p);

	return points;
}

void Engine::PrimitiveObj::Polygon::ResetVertex()
{
	for (auto p : vertex)
		delete p;
	vertex.clear();
	vertex.shrink_to_fit();
}