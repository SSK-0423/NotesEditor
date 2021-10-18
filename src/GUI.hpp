#pragma once

/*
* GUIƒNƒ‰ƒX
*/

namespace Engine
{
	namespace Components
	{
		class Transform;
	}
	namespace UI
	{
		class GUI {
		protected:
			Components::Transform* transform;
		public:
			GUI();
			virtual ~GUI();
			virtual void Draw() = 0;
			virtual void Update() = 0;
			Components::Transform& GetTransform();
		};
	}

}