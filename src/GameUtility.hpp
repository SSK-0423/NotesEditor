#pragma once
#include <cmath>

// ゲーム開発で使う構造体や定数、小規模関数をまとめたファイル

enum RESULT
{
	RESULT_SUCCEED = 0,
	RESULT_ERROR = -1
};

const int NONE = -1;

// 色
using Color = unsigned int;
// 画像
using Image = int;
// オーディオ
using Audio = int;
// フォント
using Font = int;
// 角度
using Degree = float;
// ラジアン
using Radian = float;

inline Radian DegreeToRadian(Degree angle)
{
	return acosf(-1.f) / 180.f * angle;
}