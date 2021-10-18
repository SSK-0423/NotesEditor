#include "GameObject.hpp"
#include "Transform.hpp"

Engine::GameObject::GameObject()
{
	transform = new Components::Transform();
	screenPos = new Components::Position();
}

Engine::GameObject::~GameObject()
{
	delete transform;
	delete screenPos;
}

const Engine::Components::Transform& Engine::GameObject::GetTransform() const
{
	return *transform;
}

Engine::Components::Transform& Engine::GameObject::GetTransform()
{
	return *transform;
}

Engine::Components::Position Engine::GameObject::GetScreenPos()
{
	return *screenPos;
}

const Engine::Components::Position Engine::GameObject::GetScreenPos() const
{
	return *screenPos;
}

void Engine::GameObject::UpdateScreenPos(Components::Position pos)
{
	*screenPos = pos;
}
