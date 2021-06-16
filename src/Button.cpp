#include "Button.hpp"
#include "Mouse.hpp"

// コンストラクタ
Button::Button() noexcept : count(0),fill(false), isPressed(false), sub(0){
	position.x = position.y = 0;
	height = 0;
	width = 0;
	buttonColor = GetColor(255, 255, 255);
	myDg = nullptr;
}

Button::~Button() noexcept {

}

void Button::Update() noexcept {
	if (IsCheckClick() == 0) {
		OnClick();
	}
}

//ボタンの描画情報の設定(座標、幅、高さ、色、塗りつぶし)
void Button::SetButtonInfo(const int x, const int y, const int w, const int h, const unsigned int color, const bool f)  noexcept {
	position.x = x;
	position.y = y;
	height = h;
	width = w;
	buttonColor = color;
	fill = f;
}

//描画
void Button::Draw() noexcept {
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

void Button::SetEventFunction(DelegateBase<void(void)>* dg) noexcept
{
	myDg = dg;
}

//クリック時に実行される関数
int Button::OnClick()  noexcept {
	// 関数が設定されてないなら実行しない
	if (myDg == nullptr) {
		return -1;
	}
	else {
		(*myDg)();
		return 0;
	}
}

int Button::IsCheckClick()  noexcept {
	int mouse_x, mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);//マウスの座標取得
	//マウスがボタンに乗っている時
	if (position.x - width / 2 < mouse_x && mouse_x < position.x + width / 2 && mouse_y > position.y - height / 2 && mouse_y < position.y + height / 2) {
		Mouse::Instance()->Update();
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
		return -1;
	}
	else {
		sub = 0;
		fill = false;
		isPressed = false;
		return -1;
	}
}

void Button::SetImageHandle(const char* file_name) noexcept{
	handle.push_back(LoadGraph(file_name));
	SetDrawMode(DX_DRAWMODE_BILINEAR);
}