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
		static float stepPosX;
		static Color laneColor[2];
		Color color;
		int laneNum;
		Engine::PrimitiveObj::Point* startPoint;
		Engine::PrimitiveObj::Point* endPoint;

	public:
		Lane(int laneNum, float posX);
		~Lane();
		void Update();
		void Draw();
	};
}