#pragma once
namespace Game
{
	namespace Component
	{
		using Degree = float;
		class Rotation {
		private:
			float angle;

		public:
			Rotation() : angle(0.f) {}
			Rotation(Degree angle) : angle(angle) {}

			float GetAngle()
			{
				return angle;
			}
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