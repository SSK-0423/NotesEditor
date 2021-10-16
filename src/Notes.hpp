#pragma once
#include "GameObject.hpp"

namespace Engine
{
	namespace Components
	{
		class ICollider;
	}
	namespace Collision
	{
		class PointWithPolygon;
	}
}

namespace NotesEditor
{
	enum class NOTESTYPE {
		SHORT_NOTES,		//ショートノーツ
		LONG_NOTES,			//ロングノーツ
		SLIDE_NOTES,		//スライドノーツ
		TYPENUM				//ノーツの種類数
	};

	class Notes : public Engine::GameObject {
	protected:
		// 判定タイミング
		float timing;
		// ノーツが属するレーン
		int lane;

		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;

	public:
		Notes();
		virtual ~Notes();
		float GetTiming();
		int GetLane();
		virtual void Draw() = 0;
		virtual void Update() = 0;
		virtual bool Collision(float x, float y) = 0;
		virtual NOTESTYPE GetNotesType() = 0;
	};

}