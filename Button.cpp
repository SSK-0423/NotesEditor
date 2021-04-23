#include "Button.hpp"
#include "Mouse.hpp"

// コンストラクタ
Button::Button() {
	position.x = position.y = 0;
	height = 0;
	width = 0;
	count = 0;
	buttonColor = GetColor(255, 255, 255);
	fill = false;
	isPressed = false;
	sub = 0;
	myDg = nullptr;
}

Button::~Button() {

}

void Button::Update() {
	CheckClick();//ボタンクリックチェック
}

//ボタンの描画情報の設定(座標、幅、高さ、色、塗りつぶし)
void Button::SetButtonInfo(const int x, const int y, const int w, const int h, const unsigned int color, const bool f) {
	position.x = x;
	position.y = y;
	height = h;
	width = w;
	buttonColor = color;
	fill = f;
}

//描画
void Button::Draw() {
	if (handle.size() == 0) {
		DrawBox(position.x - width / 2 + sub, position.y - height / 2 + sub, position.x + width / 2 - sub, position.y + height / 2 - sub, buttonColor, fill);
	}
	else {
		DrawModiGraph(
			position.x - width / 2 + sub, position.y - height / 2 + sub, //左上座標
			position.x + width / 2 - sub, position.y - height / 2 + sub, //右上座標
			position.x + width / 2 - sub, position.y + height / 2 - sub, //右下座標
			position.x - width / 2 + sub, position.y + height / 2 - sub, //左下座標
			handle[count % handle.size()], true); //グラフィックハンドル、透過処理
	}
}

void Button::SetEventFunction(DelegateBase<void(void)>* dg)
{
	myDg = dg;
}

//クリック時に実行される関数
int Button::OnClick() {
	// 関数が設定されてないなら実行しない
	if (myDg == nullptr) {
		return -1;
	}
	else {
		(*myDg)();
		return 0;
	}
}

int Button::CheckClick() {
	int mouse_x, mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);//マウスの座標取得
	//マウスポインタがボタンに乗っている時
	if (position.x - width / 2 < mouse_x && mouse_x < position.x + width / 2 && mouse_y > position.y - height / 2 && mouse_y < position.y + height / 2) {
		Mouse::Instance()->Update();
		//DrawFormatString(0, 400, buttonColor, "ボタンの上に乗っています");
		fill = true;
		if (Mouse::Instance()->GetPressingCount(Mouse::LEFT_CLICK) > 0) {
			isPressed = true;
			sub = 2;
		}
		//ボタンが押されている間
		if (isPressed) {
			if (Mouse::Instance()->GetPressingCount(Mouse::LEFT_CLICK) == 0) {
				isPressed = false;
				sub = 0;
				count++;
				return 0;
			}
		}
	}
	else {
		sub = 0;
		fill = false;
		isPressed = false;
		return -1;
	}
}

void Button::SetImageHandle(const char* file_name) {
	handle.push_back(LoadGraph(file_name));
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//GetGraphSize(handle[0], &width, &height);
}