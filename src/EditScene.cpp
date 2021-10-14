#include "EditScene.hpp"
#include "WindowSize.hpp"
#include "InputDeviceContainer.hpp"
#include "NotesEditorMusic.hpp"
#include "NotesManager.hpp"
#include "BarManager.hpp"
#include "LaneManager.hpp"
#include "FumenJsonGenerator.hpp"
#include "FumenJsonLoader.hpp"
#include "NotesData.hpp"
#include "DxLib.h"
#include <math.h>

const int PLUS = 1;

NotesEditor::EditScene::EditScene(Engine::Scene::ISceneChanger* changer)
	: BaseScene(changer), camera(allObjList), notesEditorMusic(NotesEditorMusic::Instance()), notesManager(NotesManager::Instance()),
	laneManager(LaneManager::Instance()), barManager(BarManager::Instance()),
	fumenJsonGenerator(FumenJsonGenerator::Instance()), fumenJsonLoader(FumenJsonLoader::Instance())
{
	editorSceneCanvas.Init();
	fumenJsonGenerator.SetNotesList(notesManager.GetNotesListRef());
	fumenJsonGenerator.SetNotesEditorMusic(notesEditorMusic);
	fumenJsonLoader.SetObjList(allObjList);
	fumenJsonLoader.SetNotesList(notesManager.GetNotesListRef());
	fumenJsonLoader.SetNotesEditorMusic(notesEditorMusic);
	
	laneHandle = LoadGraph("image/���[��02.png");
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
	float nowCameraBottonPosY = camera.GetTransform().GetPosition().y + camera.GetTransform().GetSize().height / 2.f;
	notesEditorMusic.SetCurrentTime(CalcJudgeTiming(nowCameraBottonPosY) * 1000.f);
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
	if (mouse.IsPressKey(Engine::Input::Mouse::LEFT_CLICK))
	{
		PutNotes();
	}
	if (mouse.GetPressingCount(Engine::Input::Mouse::LEFT_CLICK) > 31)
	{
		PutNotes();
	}
	if (mouse.IsPressKey(Engine::Input::Mouse::RIGHT_CLICK))
	{
		RemoveNotes();
	}
	if (mouse.GetPressingCount(Engine::Input::Mouse::RIGHT_CLICK) > 31)
	{
		RemoveNotes();
	}

	const Engine::Input::Keyboard keyboard = Engine::Input::InputDeviceContainer::Instance().GetKeyboard();
	if (keyboard.GetPressingCount(KEY_INPUT_LCONTROL) && keyboard.GetPressingCount(KEY_INPUT_S))
		fumenJsonGenerator.SaveFumen();

	if (keyboard.IsPressKey(KEY_INPUT_G))
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
}

void NotesEditor::EditScene::DecidePutPos()
{
}

void NotesEditor::EditScene::RemoveNotes()
{
	// �ݒu�ʒu���聨���[���擾�E����^�C�~���O�v�Z���ݒu
	const Engine::Input::Mouse mouse = Engine::Input::InputDeviceContainer::Instance().GetMouse();

	// �m�[�c�̐ݒu�ʒu����
	float x = mouse.GetPosX();
	float y = mouse.GetPosY() + camera.GetOriginPos().y;

	// �����Ȑݒu�ꏊ
	if (x == -1 || y == -1)
		return;

	notesManager.DeleteNotes(x, y, allObjList);
}

void NotesEditor::EditScene::PutNotes()
{
	// �ݒu�ʒu���聨���[���擾�E����^�C�~���O�v�Z���ݒu
	const Engine::Input::Mouse mouse = Engine::Input::InputDeviceContainer::Instance().GetMouse();

	// �m�[�c�̐ݒu�ʒu����
	float x = laneManager.Collision(mouse.GetPosX());
	float y = barManager.Collision(mouse.GetPosX() + camera.GetOriginPos().x, mouse.GetPosY() + camera.GetOriginPos().y);

	// �����Ȑݒu�ꏊ
	if (y == -1)
		return;

	int lane = laneManager.GetLane(x);
	float timing = CalcJudgeTiming(y);

	NotesData data(x, y, lane, timing);
	notesManager.CreateNotes(data, allObjList);
}

float NotesEditor::EditScene::CalcJudgeTiming(float y)
{
	// �ŏ��P�ʉ���������̍��W
	float minimunNoteTimeLength = static_cast<float>(WINDOW_SIZE_HEIGHT) / BarManager::MAXNOTENUM;
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

	int minimum = 4;

	for (int i = 0; i < minimum * (barManager.GetBarNum() - 1); i++)
	{
		float y = static_cast<float>(WINDOW_SIZE_HEIGHT) - static_cast<float>(WINDOW_SIZE_HEIGHT) /
			static_cast<float>(minimum) * static_cast<float>(i);

		float timing = CalcJudgeTiming(y);
		NotesData data(x, y, lane, timing);
		notesManager.CreateNotes(data, allObjList);
	}
}