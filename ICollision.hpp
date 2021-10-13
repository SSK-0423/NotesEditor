#pragma once
namespace Component 
{
	namespace Collision 
	{
		class ICollision {
		public:
			virtual bool Collision() = 0;
		};
	}
}