#pragma once

namespace Engine
{
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