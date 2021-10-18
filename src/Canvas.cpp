#include "Canvas.hpp"
#include "GUI.hpp"

Engine::UI::Canvas::Canvas()
{
}

Engine::UI::Canvas::~Canvas()
{
	for (auto gui : guiList)
		delete gui;
	guiList.clear();
	guiList.shrink_to_fit();
}

void Engine::UI::Canvas::AddGUIObj(GUI& obj)
{
	guiList.push_back(&obj);
}
