#pragma once
#include "ShortNotes.hpp"
#include "CubicSpline.hpp"
#include "Vector2.hpp"
#include <vector>

namespace NotesEditor
{
	class SlideNotes : public Notes {
	private:
		// 3次スプライン補間クラス
		CubicSpline cubicSpline;
		// ノーツリスト
		std::vector<ShortNotes*> notesList;
		// 描画座標リスト
		vector<float> dx_;
		// 描画座標リスト
		vector<float> dy_;
		// width計算
		float CalcWidth();
		// height計算
		float CalcHeight();
		// 始点から終点ノーツまでのx座標の最大値取得
		float GetMaxPosX();
		// 始点から終点ノーツまでのx座標の最小値取得
		float GetMinPosX();
		// 補間点セット
		void SetInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i);
		// 補間点計算
		Vector2<float> CalcInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i, int j);
		// カーブの描画
		void DrawCurve();
		// デバッグ用描画
		void DebugDraw();
		// 中間点セット
		void SetPoint();
		// 初期化
		void Init();

	public:
		SlideNotes(std::vector<ShortNotes*> list);
		~SlideNotes();
		bool Collision(float x, float y);
		NOTESTYPE GetNotesType();
		void Update() override;
		void Draw() override;
		void SetNotesList(std::vector<ShortNotes*> notesList);
	};
}