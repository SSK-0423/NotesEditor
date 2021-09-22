#include "Polygon.hpp"

Game::Object::Polygon::Polygon::Polygon()
{
}

Game::Object::Polygon::Polygon::~Polygon()
{
}

void Game::Object::Polygon::Polygon::Draw()
{
	for (auto p : points) 
	{

	}
}

void Game::Object::Polygon::Polygon::AddPoint(const Point& point)
{
	points.push_back(point);
}
