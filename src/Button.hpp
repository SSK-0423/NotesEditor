#pragma once
#include "DxLib.h"
#include "Delegate.hpp"
#include <vector>
#include "Vector2D.hpp"
#include "GameObject.hpp"

// ボタンが押されている間のサイズ縮小幅
const int SIZEDIFF = 2;

class Button : public GameObject {
private:
	int count;							// ボタンが押された回数（押された場合にボタンを切り替える際に使用）

	unsigned int buttonColor;			//ボタンの色

	std::vector<int> handle;			// ボタンの画像ハンドル

	int sub;							// ボタンが押された際にどれだけ大きさを変えるか

	bool fill;							// ボタンを埋めるか

	DelegateBase<void(void)>* myDg;		// デリゲート

	void OnClick() noexcept;			//ボタンが押されたら

	bool IsClick() noexcept;			//マウスクリックのチェック
	
	bool IsOnMouse();

	bool IsMouseLeftClick();

	void NotClick();

	void ClickCount();

	void RunEvent();

	void DrawDefaultBox();

	void DrawImageBox();

	void ChangeButtonSize();
public:
	Button() noexcept;							//コンストラクタ

	~Button() noexcept;							//デストラクタ

	void Update() noexcept;						//更新

	void Draw() noexcept;						//ボタンの描画

	void SetButtonInfo(const int x, const int y, const int w, const int h, const unsigned int color = GetColor(255, 255, 255), const bool f = false) noexcept;//描画用情報の設定

	// イベント関数の設定
	// クリック時に実行される関数が格納されたDelegateオブジェクトの設定
	void SetEventFunction(DelegateBase<void(void)>* dg) noexcept;

	void SetImageHandle(const char* file_name) noexcept;// 画像の設定

};