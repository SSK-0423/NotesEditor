#pragma once
#include "GameObject.hpp"
#include "GameSymbol.hpp"
#include <vector>

namespace Engine
{
	namespace Components
	{
		class Texture;
		class ICollider;
	}
	namespace Collision
	{
		class PointWithPolygon;
	}
}

namespace NotesEditor
{
	enum class BARTYPE {
		BAR1 = 0b100000,	// 1/1
		BAR4 = 0b01000,		// 1/4
		BAR8 = 0b00100,		// 1/8
		BAR16 = 0b00010,	// 1/16
		BAR32 = 0b00001,	// 1/32
	};

	class BarLine;

	// ���ߐ��N���X
	class Bar : public Engine::GameObject {
	private:
		// 1���߂ɂ����鉹�����̍ő�l
		static const int MAXNOTENUM;
		// ���ߐ��^�C�v
		static BARTYPE nowType;

		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;
		std::vector<BarLine*> barLineList;

		//�����ߖڂ�
		int barNum;
		//���ߔԍ��`��
		void DrawBarNum();
		//���ߐ��`��
		void DrawBarLine();

	public:
		// �t�H���g
		static Font fontHandle;

		Bar(int barNum);
		~Bar();
		void Update();
		void Draw();
		bool Collision(float& x, float& y);
		static void ChangeBarType(BARTYPE type);
	};
}