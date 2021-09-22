#include "PointWithPolygon.hpp"
#include "Polygon.hpp"
#include "CrossingNumberAlgorithm.hpp"
#include "ICollider.hpp"
#include "Point.hpp"

bool Game::Component::Collision::PointWithPolygon::Collision(const Object::Polygon::Point& point, const Component::Collider::ICollider& collider)
{
	CrossingNumberAlgorithm collision;
	return collision.Collision(point,collider.GetPolygon());
}
