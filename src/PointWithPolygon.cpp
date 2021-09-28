#include "PointWithPolygon.hpp"
#include "ICollider.hpp"
#include "CrossingNumberAlgorithm.hpp"
#include "Polygon.hpp"

// static変数実体化
//Component::Collision::CrossingNumberAlgorithm Component::Collision::PointWithPolygon::collision;

Component::Collision::PointWithPolygon::PointWithPolygon()
{
}

bool Component::Collision::PointWithPolygon::Collision(const PolygonObject::Point& point, const Collider::ICollider& collider)
{
	return collision.Collision(point, collider.GetPolygon());
}
