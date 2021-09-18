//#include "DxLib.h"
//#include "WindowSize.hpp"
//#include "Bar.hpp"
//#include "BarManager.hpp"
//#include <math.h>
//
////static�ϐ��̎��̉�
//int Bar::fontHandle;
//
//int Bar::lane[6];
//
//Bar::Bar(int handle, int i) noexcept : barNum(i) {
//	imageHandle = handle;
//	GetGraphSize(handle, &width, &height);
//	position.x = WINDOW_SIZE_WIDTH / 2;
//	position.y = WINDOW_SIZE_HEIGHT / 2 - height * (WINDOW_SIZE_HEIGHT / height) * i;
//	collisionPos.x = WINDOW_SIZE_WIDTH / 2;
//	collisionPos.y = WINDOW_SIZE_HEIGHT / 2 - height * (WINDOW_SIZE_HEIGHT / height) * i;
//
//	if (barNum == 0) {
//		InitLaneArray();
//	}
//}
//
//Bar::~Bar() noexcept {
//
//}
//
//void Bar::Update() noexcept {
//}
//
//void Bar::Draw() noexcept {
//	DrawModiGraph(
//		position.x - (float)width / 2, position.y - (float)height / 2, //������W
//		position.x + (float)width / 2, position.y - (float)height / 2, //�E����W
//		position.x + (float)width / 2, position.y + (float)height / 2, //�E�����W
//		position.x - (float)width / 2, position.y + (float)height / 2, //�������W
//		imageHandle, true); //�O���t�B�b�N�n���h���A���ߏ���
//	DrawFormatStringToHandle(780, position.y + (float)height / 2 - 20, GetColor(255, 255, 255), fontHandle, "%d", barNum + 1);
//	DebugDraw();
//}
//
////�����蔻��
//void Bar::Collision(float& posX, float& posY) noexcept {
//	int x, y;
//	GetMousePoint(&x, &y);
//	//DrawFormatString(800, 400, GetColor(0, 255, 0), "�����蔻����s");
//	if (CollisionBar(x, y)) {
//		//DrawFormatString(800, 450, GetColor(0, 255, 0), "%d���ߖ�", barNum + 1);
//		posX = CollisionLane(x);
//		posY = CollisionLine(y);
//	}
//}
//
//bool Bar::CollisionBar(int& x, int& y) noexcept {
//	if (x >= position.x - width / 4 && x <= position.x + width / 4 &&
//		y >= position.y - height / 2 && y <= position.y + height / 2) {
//		return true;
//	}
//	return false;
//}
//
////���[������
//float Bar::CollisionLane(int& x) noexcept {
//	//�����̍ŏ��l�ݒ�
//	int min = abs(lane[0] - x);
//	int laneIndex = 0;
//	for (int i = 1; i < 6; i++) {
//		if (min > abs(lane[i] - x)) {
//			min = abs(lane[i] - x);
//			laneIndex = i;
//		}
//	}
//	return lane[laneIndex];
//}
//
////�����ڂȂ̂��𔻒�
//float Bar::CollisionLine(int& y) noexcept {
//
//	//���ߐ��̊J�n�ʒu����̋���
//	std::vector<int> linePosYList;
//	MakeLineCollisionList(linePosYList);
//
//	//�`����W���g���Ĕ���
//	float startBarPosY = this->position.y + height / 2;
//	//�����̍ŏ�����
//	int min = abs(startBarPosY - y);
//	//�����C���f�b�N�X
//	int lineIndex = 0;
//	//���菈��
//	for (int i = 1; i < linePosYList.size(); i++) {
//		if (min > abs(startBarPosY - linePosYList[i] - y)) {
//			min = abs(startBarPosY - linePosYList[i] - y);
//			lineIndex = i;
//		}
//	}
//	//���ߐ�����̑��΍��W�����΍��W�ɕϊ�
//	float posY = this->collisionPos.y + height / 2 - linePosYList[lineIndex];
//	return posY;
//}
//
//void Bar::DebugDraw() noexcept {
//	if (barNum == 3) {
//		int x, y;
//		GetMousePoint(&x, &y);
//		unsigned int c = GetColor(0, 255, 0);
//	}
//}
//
//void Bar::MakeLineCollisionList(std::vector<int>& list) noexcept {
//	switch (BarManager::GetBarType())
//	{
//	case BAR1:
//		MakeList(list, 1);
//		break;
//	case BAR4:
//		MakeList(list, 4);
//		break;
//	case BAR8:
//		MakeList(list, 8);
//		break;
//	case BAR16:
//		MakeList(list, 16);
//		break;
//	case BAR32:
//		MakeList(list, 32);
//		break;
//	default:
//		break;
//	}
//}
//
////���X�g�쐬
//void Bar::MakeList(std::vector<int>& list, int lineNum) noexcept {
//	//���ߐ��̊J�n�ʒu�Ƃ̔���ɕK�v
//	list.push_back(0);
//	for (int i = 0; i < lineNum; i++) {
//		list.push_back(height / lineNum * (i + 1));
//	}
//}
//
//void Bar::InitLaneArray() noexcept {
//	lane[0] = 307;
//	lane[1] = 390;
//	lane[2] = 472;
//	lane[3] = 555;
//	lane[4] = 637;
//	lane[5] = 720;
//}