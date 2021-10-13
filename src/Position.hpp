#pragma once
#include "DxLib.h"
/*
	オブジェクトの座標を保持するクラス
*/

namespace Engine
{
	namespace Components 
	{

		class Position {
		public:
			float x;
			float y;
			
			Position() :x(0), y(0) {}
			Position(float x, float y) :x(x), y(y) {}

			// 移動
			void Translate(float x, float y)
			{
				this->x += x;
				this->y += y;
			}
			// 座標セット
			void SetPosition(float x, float y)
			{
				this->x = x;
				this->y = y;
			}
		};
	}
}