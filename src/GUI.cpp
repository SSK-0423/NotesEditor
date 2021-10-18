#include "GUI.hpp"
#include "Transform.hpp"

Engine::UI::GUI::GUI() : transform(nullptr)
{
	transform = new Engine::Components::Transform();
}

Engine::UI::GUI::~GUI()
{
	delete transform;
}

Engine::Components::Transform& Engine::UI::GUI::GetTransform()
{
	return *transform;
}
