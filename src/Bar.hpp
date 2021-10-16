#pragma once
#include "GameObject.hpp"
#include "GameUtility.hpp"
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

	// è¨êﬂê¸ÉNÉâÉX
	class Bar : public Engine::GameObject {
	private:
		static BARTYPE nowType;

		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;
		std::vector<BarLine*> barLineList;

		int barNum;
		void DrawBarNum();
		void DrawBarLine();

	public:
		static Font fontHandle;
		static int MAXNOTENUM;	// 1è¨êﬂÇ…Ç®ÇØÇÈâπïÑêîÇÃç≈ëÂíl

		Bar(int barNum, int lineNum);
		~Bar();
		void Update();
		void Draw();
		float Collision(float x, float y);
		static void ChangeBarType(BARTYPE type);
	};
}