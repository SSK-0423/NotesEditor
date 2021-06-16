#include "Button.hpp"
#include "Mouse.hpp"

// �R���X�g���N�^
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

//�{�^���̕`����̐ݒ�(���W�A���A�����A�F�A�h��Ԃ�)
void Button::SetButtonInfo(const int x, const int y, const int w, const int h, const unsigned int color, const bool f)  noexcept {
	position.x = x;
	position.y = y;
	height = h;
	width = w;
	buttonColor = color;
	fill = f;
}

//�`��
void Button::Draw() noexcept {
	if (handle.size() == 0) {
		DrawBox(position.x - width / 2 + sub, position.y - height / 2 + sub, position.x + width / 2 - sub, position.y + height / 2 - sub, buttonColor, fill);
	}
	else {
		DrawModiGraph(
			position.x - width / 2 + sub, position.y - height / 2 + sub, //������W
			position.x + width / 2 - sub, position.y - height / 2 + sub, //�E����W
			position.x + width / 2 - sub, position.y + height / 2 - sub, //�E�����W
			position.x - width / 2 + sub, position.y + height / 2 - sub, //�������W
			handle[count % handle.size()], true); //�O���t�B�b�N�n���h���A���ߏ���
	}
}

void Button::SetEventFunction(DelegateBase<void(void)>* dg) noexcept
{
	myDg = dg;
}

//�N���b�N���Ɏ��s�����֐�
int Button::OnClick()  noexcept {
	// �֐����ݒ肳��ĂȂ��Ȃ���s���Ȃ�
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
	GetMousePoint(&mouse_x, &mouse_y);//�}�E�X�̍��W�擾
	//�}�E�X���{�^���ɏ���Ă��鎞
	if (position.x - width / 2 < mouse_x && mouse_x < position.x + width / 2 && mouse_y > position.y - height / 2 && mouse_y < position.y + height / 2) {
		Mouse::Instance()->Update();
		fill = true;
		if (Mouse::Instance()->GetPressingCount(Mouse::LEFT_CLICK) > 0) {
			isPressed = true;
			sub = 2;
		}
		//�{�^����������Ă����
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