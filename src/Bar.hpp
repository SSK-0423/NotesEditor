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

	// 小節線クラス
	class Bar : public Engine::GameObject {
	private:
		// 1小節における音符数の最大値
		static const int MAXNOTENUM;
		// 小節線タイプ
		static BARTYPE nowType;

		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;
		std::vector<BarLine*> barLineList;

		//何小節目か
		int barNum;
		//小節番号描画
		void DrawBarNum();
		//小節線描画
		void DrawBarLine();

	public:
		// フォント
		static Font fontHandle;

		Bar(int barNum);
		~Bar();
		void Update();
		void Draw();
		bool Collision(float& x, float& y);
		static void ChangeBarType(BARTYPE type);
	};
}