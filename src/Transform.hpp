#pragma once
#include "Position.hpp"
#include "Rotation.hpp"
#include "Size.hpp"

/*
	���W�E�T�C�Y�E��]�𓝊��Ǘ�����N���X
*/

namespace Engine
{
	namespace Components
	{

		class Transform {
		private:
			Position position;
			Rotation rotation;
			Size size;

		public:
			Transform() {}
			// ���W
			Position GetPosition() const
			{
				return position;
			}
			void Translate(float x, float y)
			{
				position.Translate(x, y);
			}
			void SetPosition(float x, float y)
			{
				position.SetPosition(x, y);
			}

			// ��]
			Rotation GetRotation() const
			{
				return rotation;
			}
			void Rotate(Degree angle)
			{
				rotation.Rotate(angle);
			}
			void SetAngle(Degree angle)
			{
				rotation.SetAngle(angle);
			}

			// �T�C�Y
			Size GetSize() const
			{
				return size;
			}
			void SetSize(float w, float h)
			{
				size.SetSize(w, h);
			}
			void Scaling(float w, float h)
			{
				size.Scaling(w, h);
			}
		};
	}
}