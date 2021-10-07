#pragma once
#include "GameObject.hpp"

namespace NotesEditor
{
	class Notes : public Engine::GameObject
	{
	protected:
		// 判定タイミング＝小節線の末端座標 / 曲の長さ * ノーツの座標
		float timing;
		// ノーツのレーン
		int lane;
	public:
		//virtual void Put() noexcept {}

		// タイミング取得
		float GetTiming() noexcept;
		// レーン番号取得
		int GetLane() noexcept;

		virtual void Draw() = 0;
		virtual void Update() = 0;
	};

}