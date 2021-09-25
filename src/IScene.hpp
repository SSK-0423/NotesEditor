#pragma once
#include "InputDeviceContainer.hpp"

namespace Game {

	namespace Scene
	{
		class IScene {
		public:
			virtual void Init() = 0;
			virtual void Update() = 0;
			virtual void Draw() = 0;
		};
	}
}