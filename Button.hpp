#pragma once
#include "DxLib.h"
#include "Music.hpp"
#include "Delegate.hpp"
#include <vector>
//描画の左上右下座標(x,y)
struct Vector2
{
	int x;
	int y;
};

class Button {
private:
	Vector2 position; // ボタンの座標

	int height; // ボタンの高さ

	int width; // ボタンの幅

	int count;// ボタンが押された回数（押された場合にボタンを切り替える際に使用）

	unsigned int buttonColor;//ボタンの色

	std::vector<int> handle; // ボタンの画像ハンドル

	int sub; //ボタンが押された際にどれだけ大きさを変えるか

	bool fill;// ボタンを埋めるか

	bool isPressed; // ボタンが押されているかどうか

	int OnClick();//ボタンが押されたら

	void CheckClick();//マウスクリックのチェック

	DelegateBase<void(void)>* myDg; // デリゲート
public:
	Button();//コンストラクタ

	~Button();//デストラクタ

	void Update();//更新

	void Draw();//ボタンの描画
	
	void SetButtonInfo(const int x, const int y , const int w, const int h, const unsigned int color = GetColor(255,255,255), const bool f = false);//描画用情報の設定
	//ボタンの座標指定
	//void SetPosition(const int x, const int y);
	//void SetButotnInfo_Image(const int& x1, const int& y1, const int& x2, const int& y2, const unsigned int& color, const bool& f);
	// イベント関数の設定
	// クリック時に実行される関数が格納されたDelegateオブジェクトの設定
	void SetEventFunction(DelegateBase<void(void)>* dg);
	
	void SetImageHandle(const char* file_name);// 画像の設定

};