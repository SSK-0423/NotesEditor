#include "Button.hpp"
//#include "Button.hpp"
//#include "Mouse.hpp"
//
//// コンストラクタ
//Button::Button() : count(0),fill(false), sub(SIZEDIFF)
//{
//	buttonColor = GetColor(255, 255, 255);
//	myDg = nullptr;
//}
//
//Button::~Button() {
//
//}
//
//void Button::Update() 
//{
//	Mouse::Instance()->Update();
//
//	if (IsOnMouse() && Mouse::Instance()->IsLeftClickRelease()) 
//		OnClick();
//
//	if (IsClick()) 
//	{
//		ChangeButtonSize();
//		return;
//	}
//	
//	NotClick();
//}
//
////ボタンの描画情報の設定(座標、幅、高さ、色、塗りつぶし)
//void Button::SetButtonInfo(const int x, const int y, const int w, const int h, const unsigned int color, const bool f)  {
//	position.x = x;
//	position.y = y;
//	height = h;
//	width = w;
//	buttonColor = color;
//	fill = f;
//}
//
////描画
//void Button::Draw() {
//	if (handle.size() == 0) {
//		DrawDefaultBox();
//		return;
//	}
//	DrawImageBox();
//}
//
//// イベント関数の設定
//void Button::SetEventFunction(DelegateBase<void(void)>* dg)
//{
//	myDg = dg;
//}
//
////クリック時に実行される関数
//void Button::OnClick()  {
//	ClickCount();
//	RunEvent();
//}
//
//bool Button::IsClick()  {
//	//ボタン上で左クリックされたら
//	if (IsOnMouse() && IsMouseLeftClick()) {
//		return true;
//	}
//	return false;
//}
//
//void Button::SetImageHandle(const char* file_name){
//	handle.push_back(LoadGraph(file_name));
//	SetDrawMode(DX_DRAWMODE_BILINEAR);
//}
//
//// マウスがボタンに乗っているか判定
//bool Button::IsOnMouse()
//{
//	int mouseX, mouseY;
//
//	GetMousePoint(&mouseX, &mouseY);
//	
//	if (position.x - width / 2 < mouseX && mouseX < position.x + width / 2 && 
//		mouseY > position.y - height / 2 && mouseY < position.y + height / 2)
//		return true;
//	
//	return false;	
//}
//
//// 左クリックされたか
//bool Button::IsMouseLeftClick()
//{
//	if (Mouse::Instance()->IsLeftClick()) {
//		return true;
//	}
//	return false;
//}
//
//// 非クリック時の処理
//void Button::NotClick() {
//	sub = 0;
//	fill = false;
//}
//
//// クリック回数カウント
//void Button::ClickCount() {
//	count++;
//}
//
//// イベント関数実行
//void Button::RunEvent()
//{
//	// 関数が設定されてないなら実行しない
//	if (myDg == nullptr) {
//		return;
//	}
//	(*myDg)();
//}
//
//// 画像未設定時のボックス描画
//void Button::DrawDefaultBox()
//{
//	DrawBox(position.x - width / 2 + sub, position.y - height / 2 + sub, position.x + width / 2 - sub, position.y + height / 2 - sub, buttonColor, fill);
//}
//
//// 画像設定ボックス描画
//void Button::DrawImageBox()
//{
//	DrawModiGraph(
//			position.x - width / 2 + sub, position.y - height / 2 + sub, //左上座標
//			position.x + width / 2 - sub, position.y - height / 2 + sub, //右上座標
//			position.x + width / 2 - sub, position.y + height / 2 - sub, //右下座標
//			position.x - width / 2 + sub, position.y + height / 2 - sub, //左下座標
//			handle[count % handle.size()], true); //グラフィックハンドル、透過処理
//}
//
//// ボタンサイズ変更
//void Button::ChangeButtonSize()
//{
//	sub = SIZEDIFF;
//}
