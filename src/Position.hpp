#pragma once
#include "DxLib.h"
/*
	�I�u�W�F�N�g�̍��W��ێ�����N���X
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

			// �ړ�
			void Translate(float x, float y)
			{
				this->x += x;
				this->y += y;
			}
			// ���W�Z�b�g
			void SetPosition(float x, float y)
			{
				this->x = x;
				this->y = y;
			}
		};
	}
}