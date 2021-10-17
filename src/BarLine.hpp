#pragma once
#include "GameObject.hpp"

/*
* ���߂̕������C���̃N���X
* 4���A8���A16�����C���Ȃ�
*/

namespace Engine
{
	namespace Components
	{
		class ICollider;
		class Transform;
	}
	namespace Collision
	{
		class PointWithPolygon;
	}
	namespace PrimitiveObj
	{
		struct Point;
	}
}

namespace NotesEditor
{
	class BarLine : public Engine::GameObject {
	private:
		static Color lineColor[4];
		static int lineThickness;
		static const float BARLINEWIDTH;
		static const float BARLINEHEIGHT;
		int lineNum; // ���Ԗڂ̃��C����
		Color color;
		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;
		const Engine::GameObject& parentBar;
		Engine::PrimitiveObj::Point* startPoint;
		Engine::PrimitiveObj::Point* endPoint;
		float CalcScreenPos();
		void InitTransform();
		void InitColor();
	public:
		static float stepPosY;
		BarLine(const Engine::GameObject& parentBar, int lineNum);
		~BarLine();
		void Update();
		void Draw();
		float DecidePutPosY(float x, float y);
	};
}