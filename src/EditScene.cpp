#include "EditScene.hpp"
#include "WindowSize.hpp"
#include "InputDeviceContainer.hpp"
#include "NotesEditorMusic.hpp"
#include "NotesManager.hpp"
#include "BarManager.hpp"
#include "LaneManager.hpp"
#include <math.h>
#include "NotesData.hpp"
#include "DxLib.h"

const int PLUS = 1;

NotesEditor::EditScene::EditScene(Engine::Scene::ISceneChanger* changer)
	: BaseScene(changer), camera(allObjList), notesEditorMusic(NotesEditorMusic::Instance()), notesManager(NotesManager::Instance()),
	laneManager(LaneManager::Instance()), barManager(BarManager::Instance())
{
	editorSceneCanvas.Init();
	laneHandle = LoadGraph("image/���[��02.png");
	int barHandle = LoadGraph("image/Bar8.png");
}

void NotesEditor::EditScene::Init()
{
}


void NotesEditor::EditScene::Update()
{
	editorSceneCanvas.Update();
	laneManager.Update();
	camera.Update();
	notesManager.Update();
	// �Ȃ̓ǂݍ��݂�����������
	if (NotesEditorMusic::Instance().IsMusicLoaded())
	{
		OnMusicLoaded();
		// isMusicLoaded�t���O��false�ɂ���
		NotesEditorMusic::Instance().CompleteMusicLoad();
	}
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().IsPressKey(KEY_INPUT_D))
	{
		DeleteObj();
	}
}


void NotesEditor::EditScene::Draw()
{
	DrawRotaGraph(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2, 1.0, 0, laneHandle, true, false);

	SetDrawMode(DX_DRAWMODE_BILINEAR);
	editorSceneCanvas.Draw();
	SetDrawMode(DX_DRAWMODE_NEAREST);
	laneManager.Draw();
	camera.Draw();
	DebugDraw();
	Input();
}

void NotesEditor::EditScene::Input()
{
	// �ݒu�ʒu���聨���[���擾�E����^�C�~���O�v�Z���ݒu
	const Engine::Input::Mouse mouse = Engine::Input::InputDeviceContainer::Instance().GetMouse();
	if (mouse.GetPressingCount(Engine::Input::Mouse::LEFT_CLICK))
	{
		PutNotes();
	}

	const Engine::Input::Keyboard key = Engine::Input::InputDeviceContainer::Instance().GetKeyboard();
	if (key.IsPressKey(KEY_INPUT_G))
		DebugPutNotes();
}

void NotesEditor::EditScene::OnMusicLoaded()
{
	editorSceneCanvas.OnMusicLoaded();
	// ��
	NotesEditor::NotesEditorMusic& music = NotesEditor::NotesEditorMusic::Instance();
	// �Ȃ̑��Đ�����
	float totalTime = static_cast<float>(music.GetTotalTime());
	// �Ȃ�BPM
	float bpm = static_cast<float>(music.GetBPM());
	// �Ȃ̔��q
	float beat = static_cast<float>(music.GetBeat());

	// 1���߂̒���
	float barTimeLength = 60.f * 1000.f / static_cast<float>(music.GetBPM()) * 4.f;
	// �ŏ������̒���
	float minimumNoteTimeLength = barTimeLength / BarManager::MAXNOTENUM;
	// �K�v�ȃ��C����
	int lineNum = static_cast<float>(totalTime) / minimumNoteTimeLength + PLUS;
	//���ߐ��̌v�Z
	int barNum = totalTime / 1000.f * bpm / (60.f * beat) + 1;

	camera.SetMinposition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f,
		static_cast<float>(-WINDOW_SIZE_HEIGHT) * static_cast<float>(barNum) + static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f);
	camera.SetMaxposition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f, static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f);

	barManager.CreateBar(allObjList, barNum, lineNum);
}

void NotesEditor::EditScene::DeleteObj()
{
	for (auto obj : allObjList)
	{
		delete obj;
	}
	allObjList.clear();
	allObjList.shrink_to_fit();
	camera.DeleteObj();
	barManager.Delete();
	laneManager.Delete();
}

void NotesEditor::EditScene::DebugDraw()
{
	notesManager.Draw();

	Engine::Components::Position cameraPos = camera.GetTransform().GetPosition();
	Engine::Components::Size cameraSize = camera.GetTransform().GetSize();
	//// ���߂̖��[�܂ł̕ψ�
	//float note32TimeLength = static_cast<float>(WINDOW_SIZE_HEIGHT) / 32.f;
	//float barTopEdgePos = static_cast<float>(WINDOW_SIZE_HEIGHT) / 32.f * 3239.f;
	////float barTopEdgePos = barManager.GetBarNum() * WINDOW_SIZE_HEIGHT + note32TimeLength * 5.f;
	//if (barTopEdgePos == 0) barTopEdgePos = 1;

	// �Ȃ̍Đ�����
	int totalTime = notesEditorMusic.GetTotalTime();
	// �J�����̉��[���W
	float cameraLowerEndPos = cameraPos.y + cameraSize.height / 2.f;
	// ��
	NotesEditor::NotesEditorMusic& music = NotesEditor::NotesEditorMusic::Instance();
	// 1���߂̒���
	float barTimeLength = 60.f * 1000.f / static_cast<float>(music.GetBPM()) * 4.f;
	float note32TimeLength = barTimeLength / BarManager::MAXNOTENUM;
	// �K�v�ȃ��C����
	int lineNum = static_cast<float>(totalTime) / note32TimeLength + PLUS;

	float barTopEdgePos = static_cast<float>(WINDOW_SIZE_HEIGHT) / 32.f * lineNum;
	// �J�����̉��[���W�̈ړ���
	float cameraDisplacement = fabsf(static_cast<float>(WINDOW_SIZE_HEIGHT) - cameraLowerEndPos);
	// 1���W������̌o�ߎ���(ms)
	float elapsedTimePerY = static_cast<float>(totalTime) / static_cast<float>(barTopEdgePos);
	// �o�ߎ���(ms) = �Ȃ̍Đ�����(ms) / ���߂̖��[�܂ł̕ψ� * �J�����̉��[���W
	int elapsedTime = elapsedTimePerY * cameraDisplacement;

	DrawFormatString(700, 275, GetColor(0, 255, 0), "�o�ߎ���(��):%d", notesEditorMusic.GetElapsedTime());
	DrawFormatString(700, 300, GetColor(0, 255, 0), "�o�ߎ���(�v�Z):%d", elapsedTime);
	DrawFormatString(700, 325, GetColor(0, 255, 0), "���߂̖��[���W:%d", barTopEdgePos);
	DrawFormatString(700, 350, GetColor(0, 255, 0), "�Ȃ̑��Đ�����:%d", totalTime);
	DrawFormatString(700, 375, GetColor(0, 255, 0), "�J�����̉��[���W:%f", cameraLowerEndPos);
	DrawFormatString(700, 400, GetColor(0, 255, 0), "�J�����̉��[���W�ψ�:%f", cameraDisplacement);
	DrawFormatString(700, 425, GetColor(0, 255, 0), "1���W������̌o�ߎ���(ms):%f", elapsedTimePerY);
	DrawFormatString(700, 450, GetColor(0, 255, 0), "�덷(ms):%d", notesEditorMusic.GetElapsedTime() - elapsedTime);

	// 1���߂̒���
	barTimeLength = 60.f * 1000.f / static_cast<float>(music.GetBPM()) * 4.f;
	note32TimeLength = barTimeLength / BarManager::MAXNOTENUM;
	// �K�v�ȃ��C����
	lineNum = static_cast<float>(totalTime) / note32TimeLength + PLUS;
	DrawFormatString(700, 500, GetColor(0, 255, 0), "32�����̒���:%f", note32TimeLength);
	DrawFormatString(700, 525, GetColor(0, 255, 0), "�����C����:%d", lineNum);
	DrawFormatString(700, 200, GetColor(0, 255, 0), "elapTime:%f", (static_cast<float>(notesEditorMusic.GetElapsedTime()) / 1000.f));
}

void NotesEditor::EditScene::DecidePutPos()
{
}

void NotesEditor::EditScene::PutNotes()
{
	// �ݒu�ʒu���聨���[���擾�E����^�C�~���O�v�Z���ݒu

	const Engine::Input::Mouse mouse = Engine::Input::InputDeviceContainer::Instance().GetMouse();

	// �m�[�c�̐ݒu�ʒu����
	float x = laneManager.Collision(mouse.GetPosX(), mouse.GetPosY());
	float y = barManager.Collision(mouse.GetPosX() + camera.GetOriginPos().x, mouse.GetPosY() + camera.GetOriginPos().y);

	// �����Ȑݒu�ꏊ
	if (x == -1 || y == -1)
		return;

	int lane = laneManager.GetLane(x);
	float timing = CalcJudgeTiming(y);

	DrawFormatString(500, 175, GetColor(0, 255, 0), "x:%f,y:%f,lane:%d,timing:%f", x, y, lane, timing);

	NotesData data(x, y, lane, timing);
	notesManager.CreateNotes(data, allObjList);
}

float NotesEditor::EditScene::CalcJudgeTiming(float y)
{
	// �ŏ��P�ʉ���������̍��W
	float minimunNoteTimeLength = static_cast<float>(WINDOW_SIZE_HEIGHT) / BarManager::MAXNOTENUM;
	// 
	//float barTopEdgePos = minimunNoteTimeLength * barManager.GetLineNum();
	float barTopEdgePos = minimunNoteTimeLength * barManager.GetLineNum();

	// �Ȃ̑��Đ�����
	int totalTime = notesEditorMusic.GetTotalTime();
	// ���[����̕ψ�
	float mouseDisplacement = fabsf(static_cast<float>(WINDOW_SIZE_HEIGHT) - y);
	// �P��y���W������̌o�ߎ���(ms)
	float elapsedTimePerY = static_cast<float>(totalTime) / static_cast<float>(barTopEdgePos);
	// ����^�C�~���O(�b)
	float timing = elapsedTimePerY * mouseDisplacement / 1000.f;

	return timing;
}

void NotesEditor::EditScene::DebugPutNotes()
{
	float x = 307;
	
	int lane = 0;

	int minimum = 16;

	for (int i = 0; i < minimum * (barManager.GetBarNum() - 1); i++) 
	{
		float y = static_cast<float>(WINDOW_SIZE_HEIGHT)  - static_cast<float>(WINDOW_SIZE_HEIGHT) / 
			static_cast<float>(minimum) * static_cast<float>(i);

		float timing = CalcJudgeTiming(y);
		NotesData data(x, y, lane, timing);
		notesManager.CreateNotes(data, allObjList);
	}
}