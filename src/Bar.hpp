#pragma once
#include "GameObject.hpp"
#include "GameUtility.hpp"
#include <vector>

/*
* 小節クラス
*/

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
		static BARTYPE nowType;
		static const float BARWIDTH;
		static const float BARHEIGHT;
		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;
		std::vector<BarLine*> barLineList;
		int barNum;
		void InitPos(int barNum);
		void CreateBarLine(int lineNum);
		void UpdateBarLine();
		void DrawBarNum();
		void DrawBarLine();
		bool IsOnBar(float x, float y);
	public:
		static Font fontHandle;
		static int MAXNOTENUM;	// 1小節における音符数の最大値
		Bar(int barNum, int lineNum);
		~Bar();
		void Update();
		void Draw();
		float DecidePutPosY(float x, float y);
		void ChangedTransformByScale(float scaleHeight);
		int LineNum(float y);
		bool Collision(float x, float y);
		static void ChangeBarType(BARTYPE type);
	};
}