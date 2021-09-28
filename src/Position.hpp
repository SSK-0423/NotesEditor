#pragma once
#include "DxLib.h"
/*
	オブジェクトの座標を保持するクラス
*/

namespace Component {

	class Position {
	private:
		float posX;
		float posY;
	public:
		Position() :posX(0), posY(0) {}
		Position(float x, float y) :posX(x), posY(y) {}

		float GetPosX() const { return posX; }
		float GetPosY() const { return posY; }

		// 移動
		void Translate(float x, float y)
		{
			posX += x;
			posY += y;
		}
		// 座標セット
		void SetPosition(float x, float y)
		{
			posX = x;
			posY = y;
		}
	};
}