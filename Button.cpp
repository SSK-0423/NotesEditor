#include "Button.hpp"
#include "Mouse.hpp"

// �R���X�g���N�^
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
	CheckClick();//�{�^���N���b�N�`�F�b�N
}

//�{�^���̕`����̐ݒ�(���W�A���A�����A�F�A�h��Ԃ�)
void Button::SetButtonInfo(const int x, const int y, const int w, const int h, const unsigned int color, const bool f) {
	position.x = x;
	position.y = y;
	height = h;
	width = w;
	buttonColor = color;
	fill = f;
}

//�`��
void Button::Draw() {
	if (handle.size() == 0) {
		DrawBox(position.x - width / 2 + sub, position.y - height / 2 + sub, position.x + width / 2 - sub, position.y + height / 2 - sub, buttonColor, fill);
		//DrawString((vec1.x + vec2.x) / 2, (vec2.y + vec1.y) / 2,"�Đ�", GetColor(255, 255, 255));
	}
	else {
		//DrawRotaGraph3(100, 100, 0, 0, 1.0, 1.0, 0.0, handle, true, false);
		DrawModiGraph(
			position.x - width / 2 + sub, position.y - height / 2 + sub, //������W
			position.x + width / 2 - sub, position.y - height / 2 + sub, //�E����W
			position.x + width / 2 - sub, position.y + height / 2 - sub, //�E�����W
			position.x - width / 2 + sub, position.y + height / 2 - sub, //�������W
			handle[count % handle.size()], true); //�O���t�B�b�N�n���h���A���ߏ���
	}
}

void Button::SetEventFunction(DelegateBase<void(void)>* dg)
{
	myDg = dg;
}

//�N���b�N���Ɏ��s�����֐�
int Button::OnClick() {
	// �֐����ݒ肳��ĂȂ��Ȃ���s���Ȃ�
	if (myDg == nullptr) {
		return -1;
	}
	else {
		(*myDg)();
		return 0;
	}
}

void Button::CheckClick() {
	int mouse_x, mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);//�}�E�X�̍��W�擾
	//�}�E�X�|�C���^���{�^���ɏ���Ă��鎞
	if (position.x - width / 2 < mouse_x && mouse_x < position.x + width / 2 && mouse_y > position.y - height / 2 && mouse_y < position.y + height / 2) {
		Mouse::Instance()->Update();
		DrawFormatString(0, 400, buttonColor, "�{�^���̏�ɏ���Ă��܂�");
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
				OnClick();
			}
		}
	}
	else {
		sub = 0;
		fill = false;
		isPressed = false;
	}
}

void Button::SetImageHandle(const char* file_name) {
	handle.push_back(LoadGraph(file_name));
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//GetGraphSize(handle[0], &width, &height);
}