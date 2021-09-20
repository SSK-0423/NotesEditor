#include "Canvas.hpp"

namespace Game
{
	
	namespace Object
	{

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

			void Canvas::Input(const Input::InputDeviceContainer&)
			{
			}

			void Canvas::AddGUIObj(GUI& obj)
			{
				guiList.push_back(&obj);
			}
		}
	}
}