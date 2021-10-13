#pragma once
#include "ShortNotes.hpp"
#include "CubicSpline.hpp"
#include "Vector2.hpp"
#include "GameSymbol.hpp"
#include <vector>

namespace NotesEditor
{
	class SlideNotes : public Notes {
	private:
		// 3次スプライン補間クラス
		CubicSpline cubicSpline;
		// ノーツリスト
		std::vector<ShortNotes*> notesList;
		//
		Color notesColor;
		Color lineColor;

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
		void DrawCurve();
		void DebugDraw();
		// 中間点セット
		void SetPoint();
		// 初期化
		void Init();

	public:
		SlideNotes(std::vector<ShortNotes*> list);
		~SlideNotes();
		void PutComplete();
		void AddNotes(ShortNotes& notes);
		bool Collision(float x, float y);
		NOTESTYPE GetNotesType() override;
		void Update() override;
		void Draw() override;
		std::vector<ShortNotes*> GetChildNotesList();
	};
}