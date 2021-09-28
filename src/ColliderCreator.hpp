#pragma once
#include "Singleton.hpp"

namespace Component
{
	namespace Collider
	{
		enum class COLLIDERTYPE;
		class ICollider;
	}
	class Transform;
}

class ColliderCreator : public Singleton<ColliderCreator> {
	friend Singleton<ColliderCreator>;
private:
	ColliderCreator() {}
public:
	// ColliderÇÃê∂ê¨
	Component::Collider::ICollider* CreateCollider(Component::Collider::COLLIDERTYPE type, const Component::Transform& transform);
};