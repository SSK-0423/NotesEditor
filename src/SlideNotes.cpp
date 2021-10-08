//#include "SlideNotes.hpp"
//#include "DxLib.h"
//#include <math.h>
//
//#define INF 2000000;
//
//SlideNotes::SlideNotes(std::vector<ShortNotes*> list)  
//{
//	notesList = list;
//	Init();
//}
//
//SlideNotes::~SlideNotes()  
//{
//	for (auto obj : notesList) 
//	{
//		delete[] obj;
//	}
//	notesList.clear();
//}
//
//void SlideNotes::Init() 
//{
//	timing = 0;
//	width = CalcWidth();
//	height = fabs(notesList.back()->collisionPos.y - notesList[0]->collisionPos.y);
//	position.x = CalcColPosX();
//	collisionPos.x = CalcColPosX();
//	position.y = (notesList[0]->collisionPos.y + notesList.back()->collisionPos.y) / 2;
//	collisionPos.y = (notesList[0]->collisionPos.y + notesList.back()->collisionPos.y) / 2;
//	SetPoint();
//}
//
//void SlideNotes::Update()  
//{
//	for (auto notes : notesList) 
//	{
//		notes->SetPosition(position.x, position.y);
//	}
//}
//
//void SlideNotes::Draw()  
//{
//	DrawCurve();
//	DrawStartEnd();
//	DebugDraw();
//}
//
//void SlideNotes::SetNotesList(std::vector<ShortNotes*> list) 
//{
//	std::copy(list.begin(), list.end(), notesList.begin());
//
//	SetPoint();
//}
//
//
//void SlideNotes::SetPoint()  
//{
//	// 点の座標格納リスト
//	std::vector<vector<double>> p_;
//	p_.resize(notesList.size());
//	// 色
//	Color color = GetColor(0, 0, 255);
//
//	// 中間点の座標を代入
//	// y-xの関数なのでxとyを逆にする
//	for (int i = 0; i < notesList.size(); i++) 
//	{
//		p_[i].push_back(notesList[i]->collisionPos.y);
//		p_[i].push_back(notesList[i]->collisionPos.x);
//	}
//
//	//スプライン補間
//	cubicSpline.cubicSpline(p_, p_.size());
//	//各点間の補間点数
//	int splitNum = 100;
//
//	for (int i = 0; i < p_.size() - 1; i++)
//	{
//		// 分割数の調整
//		splitNum = fabs(p_[i + 1][0] - p_[i][0]) / 96 * 100;
//		// 2点間の距離を補間点数で割る
//		float step = fabs(p_[i + 1][0] - p_[i][0]) / splitNum;
//		SetInterpolationPoint(p_,step,splitNum,i);
//	}
//}
//
//// width計算
//int SlideNotes::CalcWidth()  
//{
//	int max = GetMaxColPosX();
//	int min = GetMinColPosX();
//	if (max == min)
//		return ShortNotes::SHORTNOTESWIDTH;
//	return abs(max - min);
//}
//
//// CollisionPosXを求める
//int SlideNotes::CalcColPosX()  
//{
//	int max = GetMaxColPosX();
//	int min = GetMinColPosX();
//	return (max + min) / 2;
//}
//
//// CollisionPosの最大値取得
//int SlideNotes::GetMaxColPosX()
//{
//	int max = -INF;
//	for (auto notes : notesList) 
//	{
//		//最大値
//		if (notes->collisionPos.x > max)
//			max = notes->collisionPos.x;
//	}
//	return max;
//}
//
//// CollsionPosの最小値取得
//int SlideNotes::GetMinColPosX()
//{
//	int min = INF;
//	for (auto notes : notesList) 
//	{
//		//最小値
//		if (notes->collisionPos.x < min)
//			min = notes->collisionPos.x;
//	}
//	return min;
//}
//
//// 補間点セット
//void SlideNotes::SetInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i)
//{
//	for (int j = 0; j < splitNum + 1; j++) 
//	{
//		Vector2<float> vec = CalcInterpolationPoint(p_, step, splitNum, i, j);
//		// x座標(y座標)代入
//		dx_.push_back(vec.y);
//		// y座標(x座標)を補間関数を用いて計算
//		dy_.push_back(vec.x);
//	}
//	// CalcInterpolationPoint(p_,step,splitNum,i);
//}
//
//// 補間点計算
//Vector2<float> SlideNotes::CalcInterpolationPoint(std::vector<vector<double>>& p_, float step, int splitNum, int i, int j)
//{
//	float x = cubicSpline.interpolation(p_[i][0] - step * (float)j, true);
//	float y = p_[i][0] - step * (float)j;
//	Vector2<float> vec;
//	vec.x = x;
//	vec.y = y;
//	return vec;
//}
//
//// x-yをy-xに変換したので、dx_ = dy_ dy = dx_
//void SlideNotes::DrawCurve()
//{
//	Color slideColor = GetColor(255, 255, 0);
//	for (int i = 1; i < dx_.size() - 1; i++) 
//	{
//		DrawBoxAA(dy_[i] + 40, position.y + (dx_[i] - dx_[0] + height / 2) + 1,
//			dy_[i] - 40, position.y + (dx_[i] - dx_[0] + height / 2) - 1, slideColor, true);
//	}
//}
//
//// 始点と終点の描画
//void SlideNotes::DrawStartEnd()
//{
//	Color StartEndColor = GetColor(255, 192, 0);
//	//始点と終点
//	DrawBoxAA(dy_[0] - 40, position.y + height / 2 - 5,
//			dy_[0] + 40, position.y + height / 2 + 5, StartEndColor, true);
//	DrawBoxAA(dy_.back() - 40, (position.y - height / 2) - 5,
//			dy_.back() + 40, (position.y - height / 2) + 5, StartEndColor, true);
//
//}
//
//// デバッグ用描画
//void SlideNotes::DebugDraw()
//{
//	int x;
//	int y;
//
//	GetMousePoint(&x, &y);
//
//	//DrawFormatString(800, 500, GetColor(0, 255, 0), "ColPosY:%f", this->collisionPos.y);
//	//DrawFormatString(800, 525, GetColor(0, 255, 0), "positionY:%f", position.y);// + dx_[0] + 5);
//	//DrawFormatString(800, 550, GetColor(0, 255, 0), "MouseX:%d,MouseY:%d", x, y);// + dx_[0] + 5);
//	//DrawFormatString(800, 575, GetColor(0, 255, 0), "width:%d", width);// + dx_[0] + 5);
//	//DrawFormatString(800, 600, GetColor(0, 255, 0), "height:%d", height);// + dx_[0] + 5);
//
//	DrawBox(position.x - width / 2, position.y - height / 2, position.x + width / 2, position.y + height / 2, GetColor(255, 0, 0), false);
//	DrawCircle(position.x, position.y, 10, GetColor(255, 255, 255), true);
//}
