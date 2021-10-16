#pragma once

/*
* オブジェクトの座標クラス
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

			void Translate(float x, float y)
			{
				this->x += x;
				this->y += y;
			}
			void SetPosition(float x, float y)
			{
				this->x = x;
				this->y = y;
			}
		};
	}
}