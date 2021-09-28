#include "PointWithPolygon.hpp"
#include "ICollider.hpp"
#include "CrossingNumberAlgorithm.hpp"
#include "Polygon.hpp"

// staticïœêîé¿ëÃâª
//Component::Collision::CrossingNumberAlgorithm Component::Collision::PointWithPolygon::collision;

Component::Collision::PointWithPolygon::PointWithPolygon()
{
}

bool Component::Collision::PointWithPolygon::Collision(const PolygonObject::Point& point, const Collider::ICollider& collider)
{
	return collision.Collision(point, collider.GetPolygon());
}
