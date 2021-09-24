#include "PointWithPolygon.hpp"
#include "ICollider.hpp"
#include "CrossingNumberAlgorithm.hpp"
#include "Polygon.hpp"

// static•Ï”À‘Ì‰»
Game::Component::Collision::CrossingNumberAlgorithm Game::Component::Collision::PointWithPolygon::collision;

bool Game::Component::Collision::PointWithPolygon::Collision(const Object::Polygon::Point& point, const Collider::ICollider& collider)
{
	return collision.Collision(point, collider.GetPolygon());
}
