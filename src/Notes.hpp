#pragma once
#include "GameObject.hpp"

/*
* ノーツの基底クラス
*/

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
		// 何小節目か
		int barNum;
		// 1小節を最小単位音符で分割した際に
		// 1小節の開始位置から何番目のラインなのか
		int lineNum;

		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;

	public:
		Notes();
		virtual ~Notes();
		float GetTiming();
		int GetLane();
		int GetBarNum();
		int GetLineNum();
		virtual void Draw() = 0;
		virtual void Update() = 0;
		virtual void ChangedTransformByScale(float size, bool isScaleUp) = 0;
		virtual bool Collision(float x, float y) = 0;
		virtual NOTESTYPE GetNotesType() = 0;
	};

}