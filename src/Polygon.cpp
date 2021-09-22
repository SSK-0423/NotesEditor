#include "Polygon.hpp"
#include "Point.hpp"
#include "DxLib.h"

Game::Object::Polygon::Polygon::Polygon() : color(GetColor(255, 255, 255))
{
}

Game::Object::Polygon::Polygon::~Polygon()
{
	for (const auto& p : vertex) {
		delete p;
	}

}

void Game::Object::Polygon::Polygon::Draw()
{
	for (size_t i = 0; i < vertex.size() - 1; i++)
		DrawLineAA(vertex[i]->x, vertex[i]->y, vertex[i + 1]->x, vertex[i + 1]->y,color, 1.f);

	// 始点と終点を結ぶ
	DrawLineAA(vertex[vertex.size() - 1]->x, vertex[vertex.size() - 1]->y, vertex[0]->x, vertex[0]->y, color, 1.f);
}

void Game::Object::Polygon::Polygon::AddPoint(float x, float y)
{
	vertex.push_back(new Point(x, y));
}

void Game::Object::Polygon::Polygon::ChangedColor(int r, int g, int b)
{
	color = GetColor(r, g, b);
}

std::vector<Game::Object::Polygon::Point> Game::Object::Polygon::Polygon::GetVertexList() const
{
	std::vector<Point> points;

	for (auto p : vertex)
	{
		points.push_back(*p);
	}
	
	return points;
}
