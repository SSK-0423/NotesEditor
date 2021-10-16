#pragma once

/*
* オブジェクトの回転クラス
*/

namespace Engine
{
	namespace Components
	{
		using Degree = float;

		class Rotation {
		public:
			Degree angle;

			Rotation() : angle(0.f) {}
			Rotation(Degree angle) : angle(angle) {}

			void Rotate(Degree angle)
			{
				this->angle += angle;
			}

			void SetAngle(Degree angle)
			{
				this->angle = angle;
			}
		};
	}
}
