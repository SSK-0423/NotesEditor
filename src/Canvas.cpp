#include "Canvas.hpp"


Engine::UI::Canvas::Canvas() noexcept
{
}

Engine::UI::Canvas::~Canvas() noexcept
{
}

void Engine::UI::Canvas::Update()
{
}

void Engine::UI::Canvas::Draw()
{
}

void Engine::UI::Canvas::AddGUIObj(GUI& obj)
{
	guiList.push_back(&obj);
}
