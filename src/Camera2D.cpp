#include "Camera2D.hpp"
#include "DxLib.h"
#include "transform.hpp"
#include "WindowSize.hpp"
#include "InputDeviceContainer.hpp"
#include "NotesEditorMusic.hpp"
#include <math.h>

const float CAMERA_WIDTH = static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f;
const float CAMERA_HEIGHT = static_cast<float>(WINDOW_SIZE_HEIGHT);

Engine::Camera2D::Camera2D(std::vector<Engine::GameObject*>& objList) : objList(objList)
{
	transform = new Components::Transform();
	transform->SetPosition(CAMERA_WIDTH, CAMERA_HEIGHT / 2.f);
	transform->SetSize(CAMERA_WIDTH, CAMERA_HEIGHT);
}

//�f�X�g���N�^
Engine::Camera2D::~Camera2D()
{
	DeleteObj();
}

void Engine::Camera2D::Update()
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
	//�����X�N���[��
	AutoScroll();
}

void Engine::Camera2D::Draw()
{
	//�f�o�b�O�p������Ȃǂ̕`��
	DebugDraw();
	//�J�������I�u�W�F�N�g�̕`��
	DrawInCameraObj();
}

//�`��I�u�W�F�N�g���X�g���X�V
void Engine::Camera2D::UpdateDrawList()
{
	drawList.clear();
	drawList.shrink_to_fit();

	for (auto obj : objList)
	{
		if (Collision(*obj))
		{
			drawList.push_back(obj);
		}
	}
}

//�J�����ɘg�ɓ�����������
bool Engine::Camera2D::Collision(const GameObject& obj)
{
	// �^�[�Q�b�g��Transform
	const Components::Transform& targetTransform = obj.GetTransform();
	// �����̊i�[
	Vector2<float> distance = CalcDistance(targetTransform);
	// �T�C�Y�̍��v�l�i�[
	Components::Size sizeSum = SumSize(targetTransform);

	// �Փ˔���
	if (distance.x <= sizeSum.width && distance.y <= sizeSum.height)
		return true;
	return false;
}

Vector2<float> Engine::Camera2D::CalcDistance(const Components::Transform& targetTransform)
{
	// �����̊i�[
	Vector2<float> distance;
	// �^�[�Q�b�g�̍��W
	Components::Position targetPos = targetTransform.GetPosition();
	// �J�����̍��W
	Components::Position cameraPos = transform->GetPosition();

	// ���S���W�̋���
	distance.x = fabsf(cameraPos.x - targetPos.x);
	distance.y = fabsf(cameraPos.y - targetPos.y);

	return distance;
}

Engine::Components::Size Engine::Camera2D::SumSize(const Components::Transform& targetTransform)
{
	// �T�C�Y�̍��v�l�i�[
	Components::Size sizeSum;
	// �^�[�Q�b�g�̃T�C�Y
	Components::Size targetSize = targetTransform.GetSize();
	// �J�����̃T�C�Y
	Components::Size cameraSize = transform->GetSize();

	// �T�C�Y�v�Z
	sizeSum.width = (cameraSize.width + targetSize.width) / 2.f;
	sizeSum.height = (cameraSize.height + targetSize.height) / 2.f;

	return sizeSum;
}

void Engine::Camera2D::AutoScroll()
{
	NotesEditor::NotesEditorMusic music = NotesEditor::NotesEditorMusic::Instance();

	if (music.IsPlaying())
	{
		// 1���߂̏c�� / ((60 * beat * speed / bpm)  * 60) = 1�t���[���̈ړ���
		float frame_move = WINDOW_SIZE_HEIGHT / 
			(music.GetBeat() * (60 / music.GetBPM()) * 60);
		transform->SetPosition(WINDOW_SIZE_WIDTH / 2, -frame_move * music.GetElapsedTime() / 1000.0f * 60.0f + WINDOW_SIZE_HEIGHT / 2);
	}
}

void Engine::Camera2D::DeleteObj() 
{
	drawList.clear();
	drawList.shrink_to_fit();
}

Engine::Components::Position Engine::Camera2D::GetOriginPos()
{
	return origin;
}

void Engine::Camera2D::UpdateOrigin()
{
	origin.x = transform->GetPosition().x - WINDOW_SIZE_WIDTH / 2.f;
	origin.y = transform->GetPosition().y - WINDOW_SIZE_HEIGHT / 2.f;
}

//�J�������I�u�W�F�N�g�̍X�V����
void Engine::Camera2D::UpdateInCameraObj()
{
	//�J�������I�u�W�F�N�g��Update�����s
	for (auto obj : drawList)
	{
		float x = obj->GetTransform().GetPosition().x - origin.x;
		float y = obj->GetTransform().GetPosition().y - origin.y;
		Components::Position updatedPos(x, y);
		obj->UpdateScreenPos(updatedPos);
		obj->Update();
	}
}

//�J�������I�u�W�F�N�g�̕`��
void Engine::Camera2D::DrawInCameraObj()
{
	for (auto obj : drawList)
	{
		obj->Draw();
	}
}

//�L�[�{�[�h,�}�E�X����
void Engine::Camera2D::Controll()
{
	// �J�����̍��W
	Components::Position cameraPos = transform->GetPosition();

	NotesEditor::NotesEditorMusic& music = NotesEditor::NotesEditorMusic::Instance();
	// bpm:1���Ԃ̓�����̔���
	// beat:1����
	// 1���̒���
	float beatTimeLength = 60.f / static_cast<float>(music.GetBPM());
	// 1���߂̒���
	float barTimeLength = 60.f / static_cast<float>(music.GetBPM()) * 4;
	// 1/32�����̒���
	//float note32TimeLength = beatTimeLength / 32.f;
	float note32TimeLength = static_cast<float>(WINDOW_SIZE_HEIGHT) / 32.f;
	//�}�E�X�z�C�[���ŃX�N���[��
	//cameraPos.y += 10 * GetMouseWheelRotVol();
	cameraPos.y += note32TimeLength * GetMouseWheelRotVol();
	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_DOWN))
		cameraPos.y += note32TimeLength;
	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_UP))
		cameraPos.y -= note32TimeLength;

	//PgUp PgDn�ŃE�B���h�E�T�C�Y���X�N���[��
	if (Input::InputDeviceContainer::Instance().GetKeyboard().IsPressKey(KEY_INPUT_PGDN))
		cameraPos.y += CAMERA_HEIGHT;
	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGUP))
		cameraPos.y -= CAMERA_HEIGHT;

	//�������ŘA���X�N���[��
	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGDN)
		&& Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGDN) % 5 == 0)
		cameraPos.y += CAMERA_HEIGHT;
	if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGUP)
		&& Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_PGUP) % 5 == 0)
		cameraPos.y -= CAMERA_HEIGHT;

	// �X�V��̍��W�Z�b�g
	transform->SetPosition(cameraPos.x, cameraPos.y);
}

//�ړ�����
void Engine::Camera2D::LimitPos()
{
	Components::Position cameraPos = transform->GetPosition();

	if (cameraPos.y < minLimitPos.y)
	{
		transform->SetPosition(cameraPos.x, minLimitPos.y);
		return;
	}
	if (cameraPos.y > maxLimitPos.y)
	{
		transform->SetPosition(cameraPos.x, maxLimitPos.y);
	}
}

void Engine::Camera2D::DebugDraw()
{
	Components::Position cameraPos = transform->GetPosition();
	Components::Size cameraSize = transform->GetSize();

	Color color = GetColor(0, 255, 0);
	// �J�����̍��W�\��
	DrawFormatString(800, 0, color, "x:%f y:%f", cameraPos.x, cameraPos.y);
	DrawFormatString(700, 25, color, "originX:%f originY:%f", origin.x,origin.y);
	DrawFormatString(800, 125, color, "objList�T�C�Y:%d", objList.size());
	DrawFormatString(800, 150, color, "drawList�T�C�Y:%d", drawList.size());
	////DrawFormatString(800, 150, color, "���߃I�u�W�F�N�g��:%d", objList[0][0]->size());
	////DrawFormatString(800, 175, color, "�m�[�c�I�u�W�F�N�g��:%d", objList[0][1]->size());
	DrawFormatString(800, 75, color, "�J�����̏�[���W:%f", cameraPos.y - cameraSize.height / 2.f);
	DrawFormatString(800, 100, color, "�J�����̉��[���W:%f", cameraPos.y + cameraSize.height / 2.f);

	// �J�����g�\��
	//DrawBox(
	//	WINDOW_SIZE_WIDTH / 2 - cameraSize.width / 2, WINDOW_SIZE_HEIGHT / 2 - cameraSize.height / 2,
	//	WINDOW_SIZE_WIDTH / 2 + cameraSize.width / 2, WINDOW_SIZE_HEIGHT / 2 + cameraSize.height / 2,
	//	GetColor(255, 255, 255), false);
}

void Engine::Camera2D::SetMinposition(float x, float y)
{
	minLimitPos.x = x;
	minLimitPos.y = y;
}

void Engine::Camera2D::SetMaxposition(float x, float y)
{
	maxLimitPos.x = x;
	maxLimitPos.y = y;
}