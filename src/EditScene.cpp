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
	fumenJsonGenerator.SetNotesList(notesManager.GetNotesListRef());
	fumenJsonGenerator.SetNotesEditorMusic(notesEditorMusic);
	fumenJsonLoader.SetObjList(allObjList);
	fumenJsonLoader.SetNotesList(notesManager.GetNotesListRef());
	fumenJsonLoader.SetNotesEditorMusic(notesEditorMusic);

	laneHandle = LoadGraph("image/���[��02.png");
}

NotesEditor::EditScene::~EditScene()
{
	allObjList.clear();
	allObjList.shrink_to_fit();
}

void NotesEditor::EditScene::Finalize()
{
	// �������Ȃ�
}

void NotesEditor::EditScene::Initialize()
{
	// �������Ȃ�
}

void NotesEditor::EditScene::Update()
{
	editorSceneCanvas.Update();
	camera.Update();
	notesManager.Update();
	UpdateStartMusicTime();
	Input();
	// �Ȃ̓ǂݍ��݂�����������
	if (NotesEditorMusic::Instance().IsMusicLoaded())
	{
		camera.Delete();
		barManager.Delete();
		if(!NotesEditorMusic::Instance().IsLoadFromFumenJson())
			allObjList.clear();
			allObjList.shrink_to_fit();
			notesManager.Delete();
		OnMusicLoaded();
		// isMusicLoaded�t���O��false�ɂ���
		NotesEditorMusic::Instance().CompleteMusicLoad();
	}
}

void NotesEditor::EditScene::Draw()
{
	DrawLaneBackground();
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	editorSceneCanvas.Draw();
	SetDrawMode(DX_DRAWMODE_NEAREST);
	laneManager.Draw();
	notesManager.Draw();
	barManager.DebugDraw();
	camera.Draw();
}

void NotesEditor::EditScene::Input()
{
	const int WAITFRAME = 32;
	const Engine::Input::Mouse mouse = Engine::Input::InputDeviceContainer::Instance().GetMouse();
	if (mouse.IsPressKey(Engine::Input::Mouse::LEFT_CLICK))
	{
		PutNotes();
	}
	if (mouse.GetPressingCount(Engine::Input::Mouse::LEFT_CLICK) > WAITFRAME)
	{
		PutNotes();
	}
	if (mouse.IsPressKey(Engine::Input::Mouse::RIGHT_CLICK))
	{
		RemoveNotes();
	}
	if (mouse.GetPressingCount(Engine::Input::Mouse::RIGHT_CLICK) > WAITFRAME)
	{
		RemoveNotes();
	}

	const Engine::Input::Keyboard keyboard = Engine::Input::InputDeviceContainer::Instance().GetKeyboard();
	if (keyboard.GetPressingCount(KEY_INPUT_LCONTROL) && keyboard.GetPressingCount(KEY_INPUT_S))
		fumenJsonGenerator.SaveFumen();
}

void NotesEditor::EditScene::OnMusicLoaded()
{
	/*
	* �J������DrawList������
	* �O�̋Ȃ̏��ߍ폜
	* �O�̋Ȃ̃m�[�c�폜
	* �e�L�X�g�{�b�N�X�̍X�V
	* ���C�����̌v�Z
	* ���ߐ��v�Z
	* �J�����̈ړ����E�ݒ�
	* ���߂̐���
	*/
	


	// �e�L�X�g�{�b�N�X�̍X�V
	editorSceneCanvas.OnMusicLoaded();

	NotesEditor::NotesEditorMusic& music = NotesEditor::NotesEditorMusic::Instance();
	long long totalTime = music.GetTotalTime();
	float bpm = static_cast<float>(music.GetBPM());
	float beat = static_cast<float>(music.GetBeat());
	int lineNum = CalcLineNum(totalTime, bpm, beat);
	int barNum = CalcBarNum(totalTime, bpm, beat);

	camera.SetMinPosition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f,
		static_cast<float>(-WINDOW_SIZE_HEIGHT) * static_cast<float>(barNum) + static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f);
	camera.SetMaxPosition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f, static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f);

	barManager.CreateBar(allObjList, barNum, lineNum);
}

void NotesEditor::EditScene::DeleteObj()
{
	allObjList.clear();
	allObjList.shrink_to_fit();
	camera.Delete();
	barManager.Delete();
}

void NotesEditor::EditScene::RemoveNotes()
{
	const Engine::Input::Mouse mouse = Engine::Input::InputDeviceContainer::Instance().GetMouse();

	float x = mouse.GetPosX();
	float y = mouse.GetPosY() + camera.GetOriginPos().y;

	notesManager.DeleteNotes(x, y, allObjList);
}

void NotesEditor::EditScene::PutNotes()
{
	// �ݒu�ʒu���聨���[���擾�E����^�C�~���O�v�Z���ݒu
	const Engine::Input::Mouse mouse = Engine::Input::InputDeviceContainer::Instance().GetMouse();

	// �m�[�c�̐ݒu�ʒu����
	float x = laneManager.DecidePutPosX(mouse.GetPosX());
	float y = barManager.DecidePutPosY(mouse.GetPosX() + camera.GetOriginPos().x, mouse.GetPosY() + camera.GetOriginPos().y);

	// �����Ȑݒu�ꏊ�Ȃ�X�L�b�v
	if (y == -1) return;

	int lane = laneManager.GetLane(x);
	float timing = CalcJudgeTiming(y);

	NotesData data(x, y, lane, timing);
	notesManager.CreateNotes(data, allObjList);
}

float NotesEditor::EditScene::CalcJudgeTiming(float y)
{
	// �ŏ��P�ʉ���������̍��W
	float minimumNotePosY = static_cast<float>(WINDOW_SIZE_HEIGHT) / BarManager::MAXNOTENUM;
	// ���߂̏�[���W
	float barTopPos = minimumNotePosY * barManager.GetLineNum();
	// �Ȃ̑��Đ�����
	long long totalTime = notesEditorMusic.GetTotalTime();
	// ���[����̕ψ�
	float mouseDisplacement = fabsf(static_cast<float>(WINDOW_SIZE_HEIGHT) - y);
	// �P��y���W������̌o�ߎ���(ms)
	float elapsedTimePerY = static_cast<float>(totalTime) / static_cast<float>(barTopPos);
	// ����^�C�~���O(�b)
	float timing = elapsedTimePerY * mouseDisplacement / 1000.f;

	return timing;
}

int NotesEditor::EditScene::CalcLineNum(long long totalTime, float bpm, float beat)
{
	const int turningNum = 1;
	// 1���߂̒���(ms)
	// 1���߂̒��� = 1��(60�b) / bpm * ���q
	// totalTime��ms�Ȃ̂�ms�ɕϊ����Čv�Z
	Msecond barTimeLength = SecToMsec(60.f) / bpm * beat;
	// �ŏ������̒���(ms)
	Msecond minimumNoteTimeLength = barTimeLength / BarManager::MAXNOTENUM;
	// ���C���� = �Ȃ̍Đ�����(ms) / �ŏ������̒���(ms)
	// ���ۂ̃��C�������1���Ȃ�
	return static_cast<float>(totalTime) / minimumNoteTimeLength + turningNum;
}

int NotesEditor::EditScene::CalcBarNum(long long totalTime, float bpm, float beat)
{
	const int turningNum = 1;
	// ���ߐ� = �Ȃ̍Đ�����(sec) * bpm / (60 * beat)
	// ���ۂ̏��ߐ����1����Ȃ��̂Œǉ�����
	return MsecToSec(static_cast<float>(totalTime)) * bpm / (60.f * beat) + turningNum;
}

void NotesEditor::EditScene::UpdateStartMusicTime()
{
	float nowCameraBottonPosY = camera.GetTransform().GetPosition().y + camera.GetTransform().GetSize().height / 2.f;
	notesEditorMusic.SetPlayStartTime(static_cast<double>(CalcJudgeTiming(nowCameraBottonPosY)) * 1000.f);
}

void NotesEditor::EditScene::DrawLaneBackground()
{
	DrawRotaGraph(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2, 1.0, 0, laneHandle, true, false);
}
