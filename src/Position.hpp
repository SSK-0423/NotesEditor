#pragma once
#include "DxLib.h"
/*
	�I�u�W�F�N�g�̍��W��ێ�����N���X
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

		// �ړ�
		void Translate(float x, float y)
		{
			posX += x;
			posY += y;
		}
		// ���W�Z�b�g
		void SetPosition(float x, float y)
		{
			posX = x;
			posY = y;
		}
	};
}