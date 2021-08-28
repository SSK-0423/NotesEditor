#include "Canvas.hpp"

Canvas::Canvas() noexcept
{
}

Canvas::~Canvas() noexcept
{
}

void Canvas::Update() noexcept
{
	for (auto obj : UIObj) {
		obj->Update();
	}
}
void Canvas::Draw() noexcept
{
	for (auto obj : UIObj) {
		obj->Draw();
	}
}

void Canvas::AddGUIObj(GUI& obj) noexcept
{
	UIObj.push_back(&obj);
}
