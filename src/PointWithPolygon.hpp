#pragma once
#include "CrossingNumberAlgorithm.hpp"

/*
* �_�Ƒ��p�`�̓��O����@�\��񋟂��郉�b�p�[�N���X
*/
namespace Engine
{
	namespace PrimitiveObj
	{
		struct Point;
	}

	namespace Components
	{
		class ICollider;
	}
	namespace Collision
	{
		class PointWithPolygon {
		private:
			static CrossingNumberAlgorithm collision;
		public:
			PointWithPolygon();
			bool Collision(float x, float y, const Components::ICollider& collider);
		};
	}
}