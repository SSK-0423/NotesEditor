#include "PointWithPolygon.hpp"
#include "ICollider.hpp"
#include "CrossingNumberAlgorithm.hpp"
#include "Point.hpp"
#include "Polygon.hpp"

// static�ϐ����̉�
//Component::Collision::CrossingNumberAlgorithm Component::Collision::PointWithPolygon::collision;

Engine::Collision::PointWithPolygon::PointWithPolygon()
{
}

bool Engine::Collision::PointWithPolygon::Collision(float x, float y, const Components::ICollider& collider)
{
	Engine::PrimitiveObj::Polygon polygon = collider.GetPolygon();
	Engine::PrimitiveObj::Point point(x, y);
	return collision.Collision(point, polygon);
}