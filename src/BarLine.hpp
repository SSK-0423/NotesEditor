#pragma once
#include "GameObject.hpp"

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

		// ‰½”Ô–Ú‚Ìƒ‰ƒCƒ“‚©
		int lineNum;
		Color color;
		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;
		const Engine::GameObject& parentBar;

		Engine::PrimitiveObj::Point* startPoint;
		Engine::PrimitiveObj::Point* endPoint;


		void InitTransform();
		void InitColor();
	public:
		static float stepPosY;

		BarLine(const Engine::GameObject& parentBar, int lineNum);
		~BarLine();
		void Update();
		void Draw();
		float Collision(float x, float y);
	};
}