#pragma once
#include "GameSymbol.hpp"
#include "Transform.hpp"

namespace Game
{
	
	namespace Object 
	{

		namespace UI
		{
			class GUI {
			protected:
				Component::Transform transform;

			public:
				virtual void Draw() = 0;
				virtual void Update() = 0;
			};
		}
	}
}