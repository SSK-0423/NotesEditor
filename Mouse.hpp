#pragma once
#include "DxLib.h"
#include "Singleton.hpp"

class Mouse : public Singleton<Mouse> {
	Mouse();//コンストラクタ
	friend Singleton<Mouse>;

public:
	static constexpr int LEFT_CLICK = 0;
	static constexpr int RIGHT_CLICK = 1;

	bool Update();	//更新
	int GetPressingCount(int keyCode);//keyCodeのキーが押されているフレーム数を取得
	int GetReleasingCount(int keyCode);//keyCodeのキーが離されているフレーム数を取得
	int GetX() { return x; }
	int GetY() { return y; }

private:
	static constexpr int KEY_NUM = 8;	//キー総数
	int x, y;
	int buttonPressingCount[KEY_NUM];//押されカウンタ
	int buttonReleasingCount[KEY_NUM];//離されカウンタ

	bool IsAvailableCode(int keyCode);//keyCodeが有効なキー番号か問う

};
