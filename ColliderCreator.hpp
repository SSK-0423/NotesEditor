#pragma once
namespace Game
{
	namespace Component 
	{
		namespace Collider
		{
			enum class COLLIDERTYPE;
			class ICollider;
		}
	}
	class ColliderCreator {
	public:
		Component::Collider::ICollider& CreateCollider(Component::Collider::COLLIDERTYPE type);
	};
}