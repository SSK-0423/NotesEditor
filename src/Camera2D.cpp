#include "Camera2D.hpp"
#include "DxLib.h"
#include "Transform.hpp"
#include "WindowSize.hpp"
#include <math.h>

const float CAMERA_WIDTH = WINDOW_SIZE_WIDTH / 2.f;
const float CAMERA_HEIGHT = WINDOW_SIZE_HEIGHT / 2.f;

Camera2D::Camera2D(std::vector<std::vector<GameObject*>*>& vec) noexcept : objList(&vec)
{
	Position2D<float> initPos;
	initPos.x = WINDOW_SIZE_WIDTH / 2.f;
	initPos.y = WINDOW_SIZE_HEIGHT / 2.f;
	transform.SetPosition(initPos);

	Size2D<float> initSize;
	initSize.width = WINDOW_SIZE_WIDTH / 2.f;
	initSize.height = WINDOW_SIZE_HEIGHT / 2.f;
	transform.SetSize(initSize);
}

//�f�X�g���N�^
Camera2D::~Camera2D() noexcept 
{
	DeleteObj();
}

void Camera2D::Update() noexcept 
{
	UpdateOrigin();
	// �J�������I�u�W�F�N�g���X�g���X�V
	UpdateDrawList();
	//�J�������I�u�W�F�N�g��Update���s
	UpdateInCameraObj();
	//�L�[�A�}�E�X����
	Controll();
	//�ړ�����
	LimitPos();
}

void Camera2D::Draw() noexcept 
{
	//�f�o�b�O�p������Ȃǂ̕`��
	DebugDraw();
	//�J�������I�u�W�F�N�g�̕`��
	DrawInCameraObj();
}

void Camera2D::Input() noexcept
{
}

//�`��I�u�W�F�N�g���X�g���X�V
void Camera2D::UpdateDrawList() noexcept 
{
	for (auto list : *objList) 
	{
		//DrawFormatString(700, 225, GetColor(0, 255, 0), "size:%d",list->size());
		for (auto obj : *list) 
		{
			//�J�����ɓ����Ă��邩���肵�ĕ`�惊�X�g�ɒǉ�
			if (Collision(*obj)) 
			{
				drawList.push_back(obj);
			}
		}
	}
}

//�J�����ɘg�ɓ�����������
bool Camera2D::Collision(const GameObject& obj) noexcept 
{
	// �^�[�Q�b�g��Transform
	const Transform& targetTransform = obj.GetTransform();
	// �����̊i�[
	Vector2<float> distance = CalcDistance(targetTransform);
	// �T�C�Y�̍��v�l�i�[
	Vector2<float> sizeSum = SumSize(targetTransform);

	// �Փ˔���
	if (distance.x <= sizeSum.x && distance.y <= sizeSum.y)
		return true;
	return false;

	const int a = 10;
	int b = a;
}

Vector2<float> Camera2D::CalcDistance(const Transform& targetTransform)
{
	// �����̊i�[
	Vector2<float> distance;
	// �^�[�Q�b�g�̍��W
	Position2D<float> targetPos = targetTransform.GetPosition();
	// �J�����̍��W
	Position2D<float> cameraPos = transform.GetPosition();
	
	// ���S���W�̋���
	distance.x = fabsf(cameraPos.x - targetPos.x);
	distance.y = fabsf(cameraPos.y - targetPos.y);

	return distance;
}

Vector2<float> Camera2D::SumSize(const Transform& targetTransform)
{
	// �T�C�Y�̍��v�l�i�[
	Vector2<float> sizeSum;
	
	// �^�[�Q�b�g�̃T�C�Y
	Size2D<float> targetSize = targetTransform.GetSize();
	// �J�����̃T�C�Y
	Size2D<float> cameraSize = transform.GetSize();

	// �T�C�Y�v�Z
	sizeSum.x = (cameraSize.width + targetSize.width) / 2.f;
	sizeSum.y = (cameraSize.height + targetSize.height) / 2.f;

	return sizeSum;
}

void Camera2D::DeleteObj() noexcept {
	drawList.clear();
	drawList.shrink_to_fit();
}

void Camera2D::UpdateOrigin()
{
	origin.x = transform.GetPosition().x -  WINDOW_SIZE_WIDTH / 2;
	origin.y = transform.GetPosition().y - WINDOW_SIZE_HEIGHT / 2;
}

//�J�������I�u�W�F�N�g�̍X�V����
void Camera2D::UpdateInCameraObj() noexcept 
{
	//�J�������I�u�W�F�N�g��Update�����s
	for (auto obj : drawList) 
	{
		obj->Update();
	}
}

//�J�������I�u�W�F�N�g�̕`��
void Camera2D::DrawInCameraObj() noexcept 
{
	for (auto obj : drawList)
	{
		//obj->position.y = obj->collisionPos.y - (this->position.y - this->collisionPos.y);
		// �X�N���[�����W�ɕϊ�

		obj->Draw();
	}
	drawList.clear();
}

//�L�[�{�[�h,�}�E�X����
void Camera2D::Controll() noexcept 
{
	gpUpdateKey();
	// �J�����̍��W
	Position2D<float> cameraPos = transform.GetPosition();

	//�}�E�X�z�C�[���ŃX�N���[��
	cameraPos.y += 10 * GetMouseWheelRotVol();

	//�㉺���L�[�ŃX�N���[��
	if (Key[KEY_INPUT_DOWN] != 0) 
	{
		cameraPos.y += 5;
	}
	if (Key[KEY_INPUT_UP] != 0) 
	{
		cameraPos.y -= 5;
	}

	//PgUp PgDn�ŃE�B���h�E�T�C�Y���X�N���[��
	if (Key[KEY_INPUT_PGDN] == 1) 
	{
		cameraPos.y += WINDOW_SIZE_HEIGHT;
	}
	if (Key[KEY_INPUT_PGUP] == 1) 
	{
		cameraPos.y -= WINDOW_SIZE_HEIGHT;
	}

	//�������ŘA���X�N���[��
	if (Key[KEY_INPUT_PGDN] != 0 && Key[KEY_INPUT_PGDN] % 5 == 0) 
	{
		cameraPos.y += WINDOW_SIZE_HEIGHT;
	}
	if (Key[KEY_INPUT_PGUP] != 0 && Key[KEY_INPUT_PGUP] % 5 == 0) 
	{
		cameraPos.y -= WINDOW_SIZE_HEIGHT;
	}

	// �X�V��̍��W�Z�b�g
	transform.SetPosition(cameraPos);
}

//�ړ�����
void Camera2D::LimitPos() noexcept
{
	Position2D<float> cameraPos = transform.GetPosition();

	if (cameraPos.y < minLimitPos.y)
	{
		cameraPos.y = minLimitPos.y;
	}
	if (cameraPos.y > maxLimitPos.y)
	{
		cameraPos.y = maxLimitPos.y;
	}
}

void Camera2D::DebugDraw() noexcept
{
	Position2D<float> cameraPos = transform.GetPosition();
	Size2D<float> cameraSize = transform.GetSize();

	Color color = GetColor(0, 255, 0);
	// �J�����̍��W�\��
	DrawFormatString(800, 0, color, "x:%f y:%f", cameraPos.x, cameraPos.y);
	DrawFormatString(800, 125, color, "objList�T�C�Y:%d", objList->size());
	DrawFormatString(800, 150, color, "���߃I�u�W�F�N�g��:%d", objList[0][0]->size());
	DrawFormatString(800, 175, color, "�m�[�c�I�u�W�F�N�g��:%d", objList[0][1]->size());
	DrawFormatString(800, 250, color, "�J�����̏�[���W:%f", cameraPos.y - cameraSize.height / 2.f);
	DrawFormatString(800, 300, color, "�J�����̉��[���W:%f", cameraPos.y + cameraSize.height / 2.f);

	// �J�����g�\��
	DrawBox(
		WINDOW_SIZE_WIDTH / 2 - cameraSize.width / 2, WINDOW_SIZE_HEIGHT / 2 - cameraSize.height / 2,
		WINDOW_SIZE_WIDTH / 2 + cameraSize.width / 2, WINDOW_SIZE_HEIGHT / 2 + cameraSize.height / 2,
		GetColor(255, 255, 255), false);
}

void Camera2D::SetMinposition(float x, float y) noexcept
{
	minLimitPos.x = x;
	minLimitPos.y = y;
}

void Camera2D::SetMaxposition(float x, float y) noexcept
{
	maxLimitPos.x = x;
	maxLimitPos.y = y;
}