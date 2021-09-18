#pragma once
#include "DxLib.h"
#include "Delegate.hpp"
#include "Game.hpp"
#include "GUI.hpp"
#include <vector>

// ボタンが押されている間のサイズ縮小幅
const int SIZEDIFF = 2;

class Button : public GUI {
private:
	// ボタンが押された回数（押された場合にボタンを切り替える際に使用）
	int count;
	//ボタンの色
	Color buttonColor;
	// ボタンの画像ハンドル
	std::vector<int> handle;
	// ボタンが押された際にどれだけ大きさを変えるか
	int sub;
	// ボタンを埋めるか
	bool fill;
	// デリゲート
	DelegateBase<void(void)>* myDg;
	// ボタンが押されたら
	void OnClick() noexcept;
	// マウスクリックのチェック
	bool IsClick() noexcept;
	// マウスがボタンの上にいるかチェック
	bool IsOnMouse();
	// 左クリックされたか
	bool IsMouseLeftClick();
	// 非クリック時の処理
	void NotClick();
	// クリック回数カウント
	void ClickCount();
	// イベント関数実行
	void RunEvent();
	// 画像未設定時のボックス描画
	void DrawDefaultBox();
	// 画像設定ボックス描画
	void DrawImageBox();
	// ボタンサイズ変更
	void ChangeButtonSize();

public:
	Button() noexcept;

	~Button() noexcept;

	void Update() noexcept;

	void Draw() noexcept;

	void SetButtonInfo(const int x, const int y, const int w, const int h, const unsigned int color = GetColor(255, 255, 255), const bool f = false) noexcept;//描画用情報の設定

	// イベント関数の設定
	// クリック時に実行される関数が格納されたDelegateオブジェクトの設定
	void SetEventFunction(DelegateBase<void(void)>* dg) noexcept;

	void SetImageHandle(const char* file_name) noexcept;// 画像の設定

};