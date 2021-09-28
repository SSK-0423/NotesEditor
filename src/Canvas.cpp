#include "Canvas.hpp"


namespace UI
{
	Canvas::Canvas() noexcept
	{
	}

	Canvas::~Canvas() noexcept
	{
	}

	void Canvas::Init()
	{
	}

	void Canvas::Update()
	{
	}

	void Canvas::Draw()
	{
	}

	void Canvas::AddGUIObj(GUI& obj)
	{
		guiList.push_back(&obj);
	}
}
