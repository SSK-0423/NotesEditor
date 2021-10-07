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
	class Lane : public Engine::GameObject{
	private:
		static int lineThickness;
		static Color laneColor;
		static float stepPosX;
		int laneNum;
		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;
		Engine::PrimitiveObj::Point* startPoint;
		Engine::PrimitiveObj::Point* endPoint;

	public:
		static int MAXLANENUM;
		//Lane(int laneNum);
		Lane(int laneNum, float posX);
		~Lane();
		void Update();
		void Draw();
		void Collision(float x, float y);
	};
}