#pragma once
#include "Position.hpp"
#include "Rotation.hpp"
#include "Size.hpp"
/*
	座標・サイズ・回転を統括管理するクラス
*/

namespace Game
{

	namespace Component
	{

		class Transform {
		private:
			Position position;
			Rotation rotation;
			Size size;

		public:
			Transform() {}
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
			Size GetSize() const
			{
				return size;
			}
			void Scalling(float x, float y)
			{
				size.Scaling(x, y);
			}
			void SetSize(float w, float h)
			{
				size.SetSize(w, h);
			}
		};
	}
}

/*
	実装メモ
	問題点：TransformがPositon2D,Size2D,Rotation2Dに依存している
	例：Position3Dが追加された→Transformに変更を加える必要がある
	例：Position2Dに正面に動く機能が追加された→Transformからそれを呼び出す機能が必要になる
	一方で、classにするときは座標の更新・回転の更新などが面倒になるのでは
	・transform.Position(),transform.Size(),transform.Rotation()
	Position→Position2Dとしても、リスコフの置換原則が満たせない
	例：z値を使用している個所
	→3D作るわけではないので...
*/