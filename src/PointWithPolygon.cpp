#include "PointWithPolygon.hpp"
#include "ICollider.hpp"
#include "CrossingNumberAlgorithm.hpp"
#include "Polygon.hpp"

// staticïœêîé¿ëÃâª
//Game::Component::Collision::CrossingNumberAlgorithm Game::Component::Collision::PointWithPolygon::collision;

Game::Component::Collision::PointWithPolygon::PointWithPolygon()
{
}

bool Game::Component::Collision::PointWithPolygon::Collision(const Object::Polygon::Point& point, const Collider::ICollider& collider)
{
	return collision.Collision(point, collider.GetPolygon());
}
