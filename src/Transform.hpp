#pragma once
#include "Position.hpp"
#include "Rotation.hpp"
#include "Size.hpp"

/*
	座標・サイズ・回転を統括管理するクラス
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
			// 座標
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

			// 回転
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

			// サイズ
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