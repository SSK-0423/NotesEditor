#pragma once
#include "Singleton.hpp"

namespace Engine
{
	namespace Components
	{
		enum class COLLIDERTYPE;
		class ICollider;
		class Transform;
	}

	class ColliderCreator : public Singleton<ColliderCreator> {
		friend Singleton<ColliderCreator>;
	
	private:
		ColliderCreator() {}

	public:
		// ColliderÇÃê∂ê¨
		Engine::Components::ICollider* CreateCollider(Engine::Components::COLLIDERTYPE type, const Engine::Components::Transform& transform);
	};
}