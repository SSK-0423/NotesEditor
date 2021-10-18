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

	laneHandle = LoadGraph("image/レーン.png");
	backgroundHandle = LoadGraph("image/背景.jpg");
}

NotesEditor::EditScene::~EditScene()
{
	InitSoundMem();
	allObjList.clear();
	allObjList.shrink_to_fit();
}

void NotesEditor::EditScene::Finalize()
{
	// 何もしない
}

void NotesEditor::EditScene::Initialize()
{
	// 何もしない
}

void NotesEditor::EditScene::Update()
{
	editorSceneCanvas.Update();
	camera.Update();
	notesManager.Update();
	UpdateStartMusicTime();
	Input();
	// 曲の読み込みが完了したら
	if (NotesEditorMusic::Instance().IsMusicLoaded())
	{
		// カメラのdrawlist初期化
		// barListの初期化
		camera.Delete();
		barManager.Delete();
		// 譜面ファイルじゃなければ
		if (!(NotesEditorMusic::Instance().IsLoadFromFumenJson()))
		{
			allObjList.clear();
			allObjList.shrink_to_fit();
			notesManager.Delete();
		}
		OnMusicLoaded();
		// isMusicLoadedフラグをfalseにする
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
	// スケールをSCALEUNIT単位で変更するために、
	// mouseWheelRotVolの符号だけ取り出して掛ける
	scale += SCALEUNIT * mouseWheelRotVol / abs(mouseWheelRotVol);
	// スケールの制限
	scale = (std::min)((std::max)(scale, MINSCALE), MAXSCALE);
	barManager.ChangedBarsTransformByScale(scale);
	notesManager.ChangedNotesTransformByScale(scale);

	// スケール変更前に編集していた小節位置にカメラを移動させる
	Engine::Components::Position cameraPos = camera.GetTransform().GetPosition();
	camera.GetTransform().SetPosition(cameraPos.x, cameraPos.y * scale / beforeScale);
	camera.ChangedScrollSpeed(scale);
	// カメラの上方向の移動限界をscaleに合わせて変更する
	camera.SetMinPosition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f,
		(static_cast<float>(-WINDOW_SIZE_HEIGHT) * static_cast<float>(barManager.GetBarNum()) + static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f) * scale);
}

void NotesEditor::EditScene::OnMusicLoaded()
{
	// テキストボックスの更新
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
	//// サイズ初期化
	scale = 1.f;
	// barのサイズ変更
	barManager.ChangedBarsTransformByScale(scale);
	// ノーツの位置変更
	notesManager.ChangedNotesTransformByScale(scale);
	// カメラのスクロールスピード変更
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

	// ノーツの設置位置決定
	float x = laneManager.DecidePutPosX(mouse.GetPosX());
	float y = barManager.DecidePutPosY(mouse.GetPosX() + camera.GetOriginPos().x, mouse.GetPosY() + camera.GetOriginPos().y);

	// 無効な設置場所ならスキップ
	if (y == -1) return;

	// ノーツデータ作成
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
	// 最小単位音符当たりの座標
	float minimumNotePosY = static_cast<float>(WINDOW_SIZE_HEIGHT) * scale / BarManager::MAXNOTENUM;
	// 小節の上端座標
	float barTopPos = minimumNotePosY * barManager.GetLineNum();
	// 曲の総再生時間(ms)
	long long totalTime = notesEditorMusic.GetTotalTime();
	// 下端からの変位
	float mouseDisplacement = fabsf(static_cast<float>(WINDOW_SIZE_HEIGHT) - y);
	// 単位y座標当たりの経過時間(ms)
	Msecond elapsedTimePerY = static_cast<float>(totalTime) / static_cast<float>(barTopPos);
	// 判定タイミング(秒)
	Second timing = MsecToSec(static_cast<double>(elapsedTimePerY) * mouseDisplacement);

	return timing;
}

int NotesEditor::EditScene::CalcLineNum(long long totalTime, float bpm, float beat)
{
	const int turningNum = 1;
	// 1小節の長さ(ms)
	// 1小節の長さ = 1分(60秒) / bpm * 拍子
	// totalTimeがmsなのでmsに変換して計算
	Msecond barTimeLength = static_cast<double>(SecToMsec(60.f)) / bpm * beat;
	// 最小音符の長さ(ms)
	Msecond minimumNoteTimeLength = barTimeLength / BarManager::MAXNOTENUM;
	// ライン数 = 曲の再生時間(ms) / 最小音符の長さ(ms)
	// 実際のライン数より1少ない
	return static_cast<float>(totalTime) / minimumNoteTimeLength + turningNum;
}

int NotesEditor::EditScene::CalcBarNum(long long totalTime, float bpm, float beat)
{
	const int turningNum = 1;
	// 小節数 = 曲の再生時間(sec) * bpm / (60 * beat)
	// 実際の小節数より1足りないので追加する
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
