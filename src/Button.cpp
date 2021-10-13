#include "Button.hpp"
//#include "Button.hpp"
//#include "Mouse.hpp"
//
//// �R���X�g���N�^
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
////�{�^���̕`����̐ݒ�(���W�A���A�����A�F�A�h��Ԃ�)
//void Button::SetButtonInfo(const int x, const int y, const int w, const int h, const unsigned int color, const bool f)  {
//	position.x = x;
//	position.y = y;
//	height = h;
//	width = w;
//	buttonColor = color;
//	fill = f;
//}
//
////�`��
//void Button::Draw() {
//	if (handle.size() == 0) {
//		DrawDefaultBox();
//		return;
//	}
//	DrawImageBox();
//}
//
//// �C�x���g�֐��̐ݒ�
//void Button::SetEventFunction(DelegateBase<void(void)>* dg)
//{
//	myDg = dg;
//}
//
////�N���b�N���Ɏ��s�����֐�
//void Button::OnClick()  {
//	ClickCount();
//	RunEvent();
//}
//
//bool Button::IsClick()  {
//	//�{�^����ō��N���b�N���ꂽ��
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
//// �}�E�X���{�^���ɏ���Ă��邩����
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
//// ���N���b�N���ꂽ��
//bool Button::IsMouseLeftClick()
//{
//	if (Mouse::Instance()->IsLeftClick()) {
//		return true;
//	}
//	return false;
//}
//
//// ��N���b�N���̏���
//void Button::NotClick() {
//	sub = 0;
//	fill = false;
//}
//
//// �N���b�N�񐔃J�E���g
//void Button::ClickCount() {
//	count++;
//}
//
//// �C�x���g�֐����s
//void Button::RunEvent()
//{
//	// �֐����ݒ肳��ĂȂ��Ȃ���s���Ȃ�
//	if (myDg == nullptr) {
//		return;
//	}
//	(*myDg)();
//}
//
//// �摜���ݒ莞�̃{�b�N�X�`��
//void Button::DrawDefaultBox()
//{
//	DrawBox(position.x - width / 2 + sub, position.y - height / 2 + sub, position.x + width / 2 - sub, position.y + height / 2 - sub, buttonColor, fill);
//}
//
//// �摜�ݒ�{�b�N�X�`��
//void Button::DrawImageBox()
//{
//	DrawModiGraph(
//			position.x - width / 2 + sub, position.y - height / 2 + sub, //������W
//			position.x + width / 2 - sub, position.y - height / 2 + sub, //�E����W
//			position.x + width / 2 - sub, position.y + height / 2 - sub, //�E�����W
//			position.x - width / 2 + sub, position.y + height / 2 - sub, //�������W
//			handle[count % handle.size()], true); //�O���t�B�b�N�n���h���A���ߏ���
//}
//
//// �{�^���T�C�Y�ύX
//void Button::ChangeButtonSize()
//{
//	sub = SIZEDIFF;
//}
