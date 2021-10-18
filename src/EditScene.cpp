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

const float NotesEditor::EditScene::MAXSCALE = 3.f;
const float NotesEditor::EditScene::MINSCALE = 0.25f;
const float NotesEditor::EditScene::SCALEUNIT = 0.25f;

NotesEditor::EditScene::EditScene(Engine::Scene::ISceneChanger* changer)
	: BaseScene(changer), camera(allObjList), notesEditorMusic(NotesEditorMusic::Instance()), notesManager(NotesManager::Instance()),
	laneManager(LaneManager::Instance()), barManager(BarManager::Instance()),
	fumenJsonGenerator(FumenJsonGenerator::Instance()), fumenJsonLoader(FumenJsonLoader::Instance()), scale(1.f)
{
	fumenJsonGenerator.SetNotesList(notesManager.GetNotesListRef());
	fumenJsonGenerator.SetNotesEditorMusic(notesEditorMusic);
	fumenJsonLoader.SetObjList(allObjList);
	fumenJsonLoader.SetNotesList(notesManager.GetNotesListRef());
	fumenJsonLoader.SetNotesEditorMusic(notesEditorMusic);

	laneHandle = LoadGraph("image/���[��.png");
	backgroundHandle = LoadGraph("image/�w�i.jpg");
}

NotesEditor::EditScene::~EditScene()
{
	InitSoundMem();
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
		// �J������drawlist������
		// barList�̏�����
		camera.Delete();
		barManager.Delete();
		// ���ʃt�@�C������Ȃ����
		if (!(NotesEditorMusic::Instance().IsLoadFromFumenJson()))
		{
			allObjList.clear();
			allObjList.shrink_to_fit();
			notesManager.Delete();
		}
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
	camera.Draw();
	notesManager.Draw();
	fumenJsonGenerator.Draw();
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

	if (keyboard.GetPressingCount(KEY_INPUT_LCONTROL) && mouse.GetMouseWheelRotVol())
	{
		OnChangedScale(mouse.GetMouseWheelRotVol());
	}
}

void NotesEditor::EditScene::OnChangedScale(int mouseWheelRotVol)
{
	float beforeScale = scale;
	// �X�P�[����SCALEUNIT�P�ʂŕύX���邽�߂ɁA
	// mouseWheelRotVol�̕����������o���Ċ|����
	scale += SCALEUNIT * mouseWheelRotVol / abs(mouseWheelRotVol);
	// �X�P�[���̐���
	scale = (std::min)((std::max)(scale, MINSCALE), MAXSCALE);
	barManager.ChangedBarsTransformByScale(scale);
	notesManager.ChangedNotesTransformByScale(scale);

	// �X�P�[���ύX�O�ɕҏW���Ă������߈ʒu�ɃJ�������ړ�������
	Engine::Components::Position cameraPos = camera.GetTransform().GetPosition();
	camera.GetTransform().SetPosition(cameraPos.x, cameraPos.y * scale / beforeScale);
	camera.ChangedScrollSpeed(scale);
	// �J�����̏�����̈ړ����E��scale�ɍ��킹�ĕύX����
	camera.SetMinPosition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f,
		(static_cast<float>(-WINDOW_SIZE_HEIGHT) * static_cast<float>(barManager.GetBarNum()) + static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f) * scale);
}

void NotesEditor::EditScene::OnMusicLoaded()
{
	// �e�L�X�g�{�b�N�X�̍X�V
	editorSceneCanvas.OnMusicLoaded();

	NotesEditor::NotesEditorMusic& music = NotesEditor::NotesEditorMusic::Instance();
	long long totalTime = music.GetTotalTime();
	float bpm = static_cast<float>(music.GetBPM());
	float beat = static_cast<float>(music.GetBeat());
	int lineNum = CalcLineNum(totalTime, bpm, beat);
	int barNum = CalcBarNum(totalTime, bpm, beat);

	barManager.CreateBar(allObjList, barNum, lineNum);

	camera.SetMinPosition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f,
		static_cast<float>(-WINDOW_SIZE_HEIGHT) * static_cast<float>(barNum) + static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f);
	camera.SetMaxPosition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f, static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f);


	notesManager.InitBeforeScale();
	//// �T�C�Y������
	scale = 1.f;
	// bar�̃T�C�Y�ύX
	barManager.ChangedBarsTransformByScale(scale);
	// �m�[�c�̈ʒu�ύX
	notesManager.ChangedNotesTransformByScale(scale);
	// �J�����̃X�N���[���X�s�[�h�ύX
	camera.ChangedScrollSpeed(scale);
}

void NotesEditor::EditScene::RemoveNotes()
{
	const Engine::Input::Mouse mouse = Engine::Input::InputDeviceContainer::Instance().GetMouse();

	float x = mouse.GetPosX();
	float y = mouse.GetPosY() + camera.GetOriginPos().y;

	notesManager.DeleteNotes(x, y, allObjList);

	fumenJsonGenerator.NotSaveCompleted();
}

void NotesEditor::EditScene::PutNotes()
{
	const Engine::Input::Mouse mouse = Engine::Input::InputDeviceContainer::Instance().GetMouse();

	// �m�[�c�̐ݒu�ʒu����
	float x = laneManager.DecidePutPosX(mouse.GetPosX());
	float y = barManager.DecidePutPosY(mouse.GetPosX() + camera.GetOriginPos().x, mouse.GetPosY() + camera.GetOriginPos().y);

	// �����Ȑݒu�ꏊ�Ȃ�X�L�b�v
	if (y == -1) return;

	// �m�[�c�f�[�^�쐬
	int lane = laneManager.GetLane(x);
	Second timing = CalcJudgeTiming(y);
	int barNum = barManager.NotesBarNum(y);
	int lineNum = barManager.NotesLineNum(y);

	NotesData data(x, y, lane, timing, barNum, lineNum);
	notesManager.CreateNotes(data, allObjList);

	fumenJsonGenerator.NotSaveCompleted();
}

float NotesEditor::EditScene::CalcJudgeTiming(float y)
{
	// �ŏ��P�ʉ���������̍��W
	float minimumNotePosY = static_cast<float>(WINDOW_SIZE_HEIGHT) * scale / BarManager::MAXNOTENUM;
	// ���߂̏�[���W
	float barTopPos = minimumNotePosY * barManager.GetLineNum();
	// �Ȃ̑��Đ�����(ms)
	long long totalTime = notesEditorMusic.GetTotalTime();
	// ���[����̕ψ�
	float mouseDisplacement = fabsf(static_cast<float>(WINDOW_SIZE_HEIGHT) - y);
	// �P��y���W������̌o�ߎ���(ms)
	Msecond elapsedTimePerY = static_cast<float>(totalTime) / static_cast<float>(barTopPos);
	// ����^�C�~���O(�b)
	Second timing = MsecToSec(static_cast<double>(elapsedTimePerY) * mouseDisplacement);

	return timing;
}

int NotesEditor::EditScene::CalcLineNum(long long totalTime, float bpm, float beat)
{
	const int turningNum = 1;
	// 1���߂̒���(ms)
	// 1���߂̒��� = 1��(60�b) / bpm * ���q
	// totalTime��ms�Ȃ̂�ms�ɕϊ����Čv�Z
	Msecond barTimeLength = static_cast<double>(SecToMsec(60.f)) / bpm * beat;
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
	DrawRotaGraph(WINDOW_SIZE_WIDTH / 2 - 100, WINDOW_SIZE_HEIGHT / 2, 0.75, 0, backgroundHandle, true, false);
	DrawRotaGraph(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2, 1.0, 0, laneHandle, true, false);
}
