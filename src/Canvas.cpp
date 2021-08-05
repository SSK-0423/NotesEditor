#include "Canvas.hpp"
#include "ComponentSystem.hpp"
Canvas::Canvas() noexcept
{

}

Canvas::~Canvas() noexcept
{
}

void Canvas::Update() noexcept
{
	for (auto obj : UI) {
		obj->Update();
	}
}
void Canvas::Draw() noexcept
{
	for (auto obj : UI) {
		obj->Draw();
	}
}

void Canvas::AddUI(GUI& obj) noexcept
{
	UI.push_back(&obj);
}
