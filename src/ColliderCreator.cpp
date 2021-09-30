#include "ColliderCreator.hpp"
#include "BoxCollider.hpp"

Engine::Components::ICollider* Engine::ColliderCreator::CreateCollider(Engine::Components::COLLIDERTYPE type, const Engine::Components::Transform& transform)
{
	switch (type)
	{
	case Engine::Components::COLLIDERTYPE::COLLIDERTYPE_BOX:
		return new Components::BoxCollider(transform);
	default:
		return nullptr;
	}
}