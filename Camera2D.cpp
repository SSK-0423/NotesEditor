#include "Camera2D.hpp"
#include "DxLib.h"
#include "WindowSize.hpp"
#include <math.h>

#define CAMERA_SIZE_WIDTH WINDOW_SIZE_WIDTH / 2
#define CAMERA_SIZE_HEIGHT WINDOW_SIZE_HEIGHT / 2

Camera2D::Camera2D(std::vector<GameObject*>& vec) noexcept : objList(&vec){
	position.x = WINDOW_SIZE_WIDTH / 2;
	position.y = WINDOW_SIZE_HEIGHT / 2;
	width = CAMERA_SIZE_WIDTH;
	height = WINDOW_SIZE_HEIGHT;
	collisionPos.x = position.x;
	collisionPos.y = position.y;
}

//�f�X�g���N�^
Camera2D::~Camera2D() noexcept {
	DeleteObj();
}

void Camera2D::Update() noexcept {
	// �J�������I�u�W�F�N�g���X�g���X�V
	UpdateDrawList();
	//�J�������I�u�W�F�N�g��Update���s
	InCameraObjUpdate();
	//�L�[�A�}�E�X����
	Controll();
	//�ړ�����
	PosLimit();
}

void Camera2D::Draw() noexcept {
	//�f�o�b�O�p������Ȃǂ̕`��
	DebugDraw();
	//�J�������I�u�W�F�N�g�̕`��
	InCameraObjDraw();
}

//�`��I�u�W�F�N�g���X�g���X�V
void Camera2D::UpdateDrawList() noexcept {
	for (auto obj : *objList) {
		//�J�����ɓ����Ă��邩���肵�ĕ`�惊�X�g�ɒǉ�
		if (Collision(*obj)) {
			drawList.push_back(obj);
		}
	}
}

//�J�����ɘg�ɓ�����������
bool Camera2D::Collision(GameObject& obj) const noexcept {
	Vector2D distance;	//�����̊i�[
	//���S���W�̋���
	distance.x = fabsf(this->position.x - obj.collisionPos.x);
	distance.y = fabsf(this->position.y - obj.collisionPos.y);

	Vector2D sizeSum;	//�T�C�Y�̊i�[
	//�T�C�Y�v�Z
	sizeSum.x = (this->width + obj.GetObjWidth()) / 2.0f;
	sizeSum.y = (this->height + obj.GetObjHeight()) / 2.0f;

	// �Փ˔���
	if (distance.x <= sizeSum.x && distance.y <= sizeSum.y) {
		return true;
	}
	else {
		return false;
	}
}

void Camera2D::DeleteObj() noexcept {
	objList->clear();
	drawList.clear();
}

//�J�������I�u�W�F�N�g�̍X�V����
void Camera2D::InCameraObjUpdate() noexcept {
	//�J�������I�u�W�F�N�g��Update�����s
	for (auto obj : drawList) {
		obj->Update();
	}
}

//�J�������I�u�W�F�N�g�̕`��
void Camera2D::InCameraObjDraw() noexcept {
	for (auto obj : drawList)
	{
		obj->position.y = obj->collisionPos.y - (this->position.y - this->collisionPos.y);
		obj->Draw();
	}
	drawList.clear();
}

//�L�[�{�[�h,�}�E�X����
void Camera2D::Controll() noexcept {
	gpUpdateKey();
	//�}�E�X�z�C�[���ŃX�N���[��
	position.y += 10 * GetMouseWheelRotVol();
	//�㉺���L�[�ŃX�N���[��
	if (Key[KEY_INPUT_DOWN] != 0) {
		position.y += 5;
	}
	if (Key[KEY_INPUT_UP] != 0) {
		position.y -= 5;
	}

	//PgUp PgDn�ŃE�B���h�E�T�C�Y���X�N���[��
	if (Key[KEY_INPUT_PGDN] == 1) {
		position.y += WINDOW_SIZE_HEIGHT;
	}
	if (Key[KEY_INPUT_PGUP] == 1) {
		position.y -= WINDOW_SIZE_HEIGHT;
	}

	//�������ŘA���X�N���[��
	if (Key[KEY_INPUT_PGDN] != 0 && Key[KEY_INPUT_PGDN] % 5 == 0) {
		position.y += WINDOW_SIZE_HEIGHT;
	}
	if (Key[KEY_INPUT_PGUP] != 0 && Key[KEY_INPUT_PGUP] % 5 == 0) {
		position.y -= WINDOW_SIZE_HEIGHT;
	}

	//objList�̏������EGameObject��delete
	if (CheckHitKey(KEY_INPUT_D) != 0) {
		//GameObject�̃������J��
		DeleteObj();
	}
}

//�ړ�����
void Camera2D::PosLimit() noexcept {
	if (position.y < minLimitPos.y) {
		position.y = minLimitPos.y;
	}
	if (position.y > maxLimitPos.y) {
		position.y = maxLimitPos.y;
	}
}

void Camera2D::DebugDraw() noexcept {
	unsigned int c = GetColor(0, 255, 0);
	// �J�����̍��W�\��
	DrawFormatString(800, 0, GetColor(0, 255, 0), "x:%f y:%f", position.x, position.y);
	DrawFormatString(800, 150, GetColor(0, 255, 0), "�I�u�W�F�N�g��:%d", objList->size());
	DrawFormatString(800, 250, GetColor(0, 255, 0), "�J�����̏�[���W:%f",position.y - height/2);
	DrawFormatString(800, 300, GetColor(0, 255, 0), "�J�����̉��[���W:%f",position.y + height/2);

	// �J�����g�\��
	DrawBox(
		WINDOW_SIZE_WIDTH / 2 - width / 2, WINDOW_SIZE_HEIGHT / 2 - height / 2,
		WINDOW_SIZE_WIDTH / 2 + width / 2, WINDOW_SIZE_HEIGHT / 2 + height / 2,
		GetColor(255, 255, 255), false);
}

void Camera2D::SetMinPosition(float x, float y) noexcept {
	minLimitPos.x = x;
	minLimitPos.y = y;
}

void Camera2D::SetMaxPosition(float x, float y) noexcept {
	maxLimitPos.x = x;
	maxLimitPos.y = y;
}