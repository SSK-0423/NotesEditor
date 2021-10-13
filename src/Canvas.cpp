#include "Canvas.hpp"


Engine::UI::Canvas::Canvas()
{
}

Engine::UI::Canvas::~Canvas()
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
