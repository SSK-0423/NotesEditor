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
		// 判定タイミング＝小節線の末端座標 / 曲の長さ * ノーツの座標
		float timing;
		// ノーツのレーン
		int lane;
		// ノーツタイプ
		NOTESTYPE type;

		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;

	public:
		virtual ~Notes();
		float GetTiming();
		int GetLane();
		virtual bool Collision(float x, float y) = 0;
		virtual NOTESTYPE GetNotesType() = 0;
		virtual void Draw() = 0;
		virtual void Update() = 0;
	};

}