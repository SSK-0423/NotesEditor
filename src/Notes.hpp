#pragma once
#include "GameObject.hpp"

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

	public:
		float GetTiming();
		int GetLane();
		NOTESTYPE GetNotesType();
		virtual void Draw() = 0;
		virtual void Update() = 0;
	};

}