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

		void InitTransform();
		void InitColor();
	public:
		BarLine(const Engine::GameObject& parentBar, int lineNum);
		~BarLine();
		void Update();
		void Draw();
		void Collision(float x, float y);
	};
}