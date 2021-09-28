#include "ColliderCreator.hpp"
#include "BoxCollider.hpp"

namespace Collider = Component::Collider;

Component::Collider::ICollider* ColliderCreator::CreateCollider(Component::Collider::COLLIDERTYPE type, const Component::Transform& transform)
{
	switch (type)
	{
	case Component::Collider::COLLIDERTYPE::COLLIDERTYPE_BOX:
		return new Component::Collider::BoxCollider(transform);
	default:
		return nullptr;
	}
}
