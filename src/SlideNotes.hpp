#pragma once
#include "ShortNotes.hpp"
#include "CubicSpline.hpp"
#include "Vector2.hpp"
#include <vector>

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
	int CalcWidth() noexcept;
	// CollisionPosXを求める
	int CalcColPosX() noexcept;
	// CollisionPosの最大値取得
	int GetMaxColPosX();
	// CollsionPosの最小値取得
	int GetMinColPosX();
	// 補間点セット
	void SetInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i);
	// 補間点計算
	Vector2<float> CalcInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i, int j);
	// カーブの描画
	void DrawCurve();
	// 始点と終点の描画
	void DrawStartEnd();
	// デバッグ用描画
	void DebugDraw();
	// 中間点セット
	void SetPoint() noexcept;
	// 初期化
	void Init();
public:
	SlideNotes(std::vector<ShortNotes*> list) noexcept;
	~SlideNotes() noexcept;
	void Update() noexcept override;
	void Draw() noexcept override;
	void SetNotesList(std::vector<ShortNotes*> notesList) noexcept;
};