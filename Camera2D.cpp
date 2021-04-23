#include "Camera2D.hpp"
#include "DxLib.h"
#include "WindowSize.hpp"
#include <math.h>

#define CAMERA_SIZE_WIDTH WINDOW_SIZE_WIDTH / 2
#define CAMERA_SIZE_HEIGHT WINDOW_SIZE_HEIGHT / 2

Camera2D::Camera2D() {
	position.x = WINDOW_SIZE_WIDTH / 2;
	position.y = WINDOW_SIZE_HEIGHT / 2;
	width = CAMERA_SIZE_WIDTH;
	height = WINDOW_SIZE_HEIGHT;
	collisionPos.x = position.x;
	collisionPos.y = position.y;
	maxPos.x = 0;
	maxPos.y = 0;
	minPos.x = 0;
	minPos.y = 0;
}

//�f�X�g���N�^
Camera2D::~Camera2D() {
	for (auto i : objList) {
		delete[] i;
	}
	for (auto i : drawList) {
		delete[] i;
	}
	objList.clear();
	drawList.clear();
}

void Camera2D::SetObject(GameObject* obj) {
	objList.push_back(obj);
}

void Camera2D::UpdateDrawList() {
	for (int i = 0; i < objList.size(); i++) {
		if (Collision(*objList[i])) {
			drawList.push_back(objList[i]);
		}
	}
}

void Camera2D::Update() {
	position.y += 10 * GetMouseWheelRotVol();
	if (CheckHitKey(KEY_INPUT_DOWN) != 0) {
		position.y -= 5;
	}
	if (CheckHitKey(KEY_INPUT_UP) != 0) {
		position.y += 5;
	}
	if (position.y < minPos.y) {
		position.y = minPos.y;
	}
	if (position.y > maxPos.y) {
		position.y = maxPos.y;
	}
	//int x, y;
	//GetMousePoint(&x, &y);
	//position.x = x;
	//position.y = y;

	// �J�������̃I�u�W�F�N�g���X�g���X�V
	UpdateDrawList();
	// �J�������I�u�W�F�N�g��Update
	for (int i = 0; i < drawList.size(); i++) {
		drawList[i]->Update();
	}
}

void Camera2D::Draw() {
	// �J�����̍��W�\��
	DrawFormatString(800, 0, GetColor(0, 255, 0), "x:%f y:%f", position.x, position.y);
	DrawFormatString(800, 150, GetColor(0, 255, 0), "�I�u�W�F�N�g��:%d", objList.size());

	// �J�����g�\��
	/*DrawBox(
		WINDOW_SIZE_WIDTH / 2 - width / 2, WINDOW_SIZE_HEIGHT / 2 - height / 2,
		WINDOW_SIZE_WIDTH / 2 + width / 2, WINDOW_SIZE_HEIGHT / 2 + height / 2,
		GetColor(255, 255, 255), false);*/

	for (auto& a : drawList)
	{
		a->position.y = a->collisionPos.y - (this->position.y - collisionPos.y);
		a->Draw();
	}

	drawList.clear();
}

//�J�����ɘg�ɓ�����������
bool Camera2D::Collision(const GameObject& obj) const {
	//DrawFormatString(500, 700, GetColor(0, 255, 0), "x:%f y:%f", obj.position.x, obj.position.y);
	Vector2D distance;	//�����̊i�[
	//���S���W�̋���
	distance.x = fabsf(this->position.x - obj.collisionPos.x);
	distance.y = fabsf(this->position.y - obj.collisionPos.y);

	Vector2D sizeSum;	//�T�C�Y�̊i�[
	//�T�C�Y�v�Z
	sizeSum.x = (this->width + obj.width) / 2.0f;
	sizeSum.y = (this->height + obj.height) / 2.0f;

	// �Փ˔���
	if (distance.x <= sizeSum.x && distance.y <= sizeSum.y) {
		//DrawFormatString(0, 100, GetColor(0, 255, 0), "������");
		return true;
	}
	else {
		//DrawFormatString(0, 100, GetColor(0, 255, 0), "�����ĂȂ�");
		return false;
	}
}

void Camera2D::DeleteObj() {
	//GameObject�̃������J��
	for (auto i : objList) {
		delete[] i;
	}
	objList.clear();
	drawList.clear();
}

void Camera2D::SetPosition(float x, float y) {
	//float frame_move = 760 / ((3600 * beat * speed) / bpm);
	//DrawFormatString(400, 200, GetColor(0, 0, 255), "beat:%d speed:%d bpm:%d count:%d", beat, speed, bpm, count);
	//DrawFormatString(400, 300, GetColor(0, 0, 255), "FrameMove:%f", frame_move);
	//// 1���߂̏c�� / ((60 * beat * speed / bpm)  * 60) = 1�t���[���̈ړ���
	//position.y = -frame_move * count + WINDOW_SIZE_HEIGHT/2;
	position.x = x;
	position.y = y;
}

void Camera2D::SetMinPosition(float x, float y) {
	minPos.x = x;
	minPos.y = y;
}

void Camera2D::SetMaxPosition(float x, float y) {
	maxPos.x = x;
	maxPos.y = y;
}
