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
}

Engine::Components::Position Engine::GameObject::GetScreenPos()
{
	return *screenPos;
}

void Engine::GameObject::UpdateScreenPos(Components::Position& pos)
{
	screenPos = &pos;
}
