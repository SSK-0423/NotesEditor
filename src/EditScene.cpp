#include "EditScene.hpp"
#include "WindowSize.hpp"
#include "InputDeviceContainer.hpp"
#include "NotesEditorMusic.hpp"
#include "NotesManager.hpp"
#include "BarManager.hpp"
#include "LaneManager.hpp"
#include <math.h>
#include "DxLib.h"

NotesEditor::EditScene::EditScene(Engine::Scene::ISceneChanger* changer)
	: BaseScene(changer), camera(allObjList), notesEditorMusic(NotesEditorMusic::Instance()), notesManager(NotesManager::Instance()),
	laneManager(LaneManager::Instance()), barManager(BarManager::Instance())
{
	editorSceneCanvas.Init();
	laneHandle = LoadGraph("image/レーン02.png");
	int barHandle = LoadGraph("image/Bar8.png");
}

void NotesEditor::EditScene::Init()
{
}

void NotesEditor::EditScene::PutNotes()
{
	const Engine::Input::Mouse mouse = Engine::Input::InputDeviceContainer::Instance().GetMouse();
	if (mouse.IsPressKey(Engine::Input::Mouse::LEFT_CLICK))
	{
		float x = laneManager.Collision(mouse.GetPosX(), mouse.GetPosY());
		float y = barManager.Collision(mouse.GetPosX() + camera.GetOriginPos().x, mouse.GetPosY() + camera.GetOriginPos().y);
		if (x == -1 || y == -1)
			return;
		
		int lane = laneManager.GetLane(x);
		
		Engine::Components::Position cameraPos = camera.GetTransform().GetPosition();
		Engine::Components::Size cameraSize = camera.GetTransform().GetSize();

		// 最小単位音符当たりの座標
		float minimunNoteTimeLength = static_cast<float>(WINDOW_SIZE_HEIGHT) / BarManager::MAXNOTENUM;
		// 
		float barTopEdgePos = minimunNoteTimeLength * barManager.GetBarNum() * BarManager::MAXNOTENUM;
		if (barTopEdgePos == 0) barTopEdgePos = 1;

		// 曲の総再生時間
		int totalTime = notesEditorMusic.GetTotalTime();
		// 下端からの変位
		float mouseDisplacement = fabsf(static_cast<float>(WINDOW_SIZE_HEIGHT) - y);
		// 単位y座標当たりの経過時間(ms)
		float elapsedTimePerY = static_cast<float>(totalTime) / static_cast<float>(barTopEdgePos);
		// 判定タイミング(秒)
		float timing = elapsedTimePerY * mouseDisplacement / 1000.f;

		DrawFormatString(500, 175, GetColor(0, 255, 0), "x:%f,y:%f,lane:%d,timing:%f", x, y, lane, timing);
	}
}

void NotesEditor::EditScene::Update()
{
	editorSceneCanvas.Update();
	laneManager.Update();
	camera.Update();

	// 曲の読み込みが完了したら
	if (NotesEditorMusic::Instance().IsMusicLoaded())
	{
		OnMusicLoaded();
		// isMusicLoadedフラグをfalseにする
		NotesEditorMusic::Instance().CompleteMusicLoad();
	}
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().IsPressKey(KEY_INPUT_D))
	{
		DeleteObj();
	}
}

void NotesEditor::EditScene::DebugDraw()
{
	//Engine::Components::Position cameraPos = camera.GetTransform().GetPosition();
	//Engine::Components::Size cameraSize = camera.GetTransform().GetSize();

	//// 小節の末端までの変位
	//float note32TimeLength = static_cast<float>(WINDOW_SIZE_HEIGHT) / 32.f;
	////float barTopEdgePos = static_cast<float>(WINDOW_SIZE_HEIGHT) / 32.f * 3239.f;
	//float barTopEdgePos = barManager.GetBarNum() * WINDOW_SIZE_HEIGHT + note32TimeLength * 6.f;
	//if (barTopEdgePos == 0) barTopEdgePos = 1;
	//// 曲の再生時間
	//int totalTime = notesEditorMusic.GetTotalTime();
	//// カメラの下端座標
	//float cameraLowerEndPos = cameraPos.y + cameraSize.height / 2.f;
	//// カメラの下端座標の移動幅
	//float cameraDisplacement = fabsf(static_cast<float>(WINDOW_SIZE_HEIGHT) - cameraLowerEndPos);
	//// 1座標当たりの経過時間(ms)
	//float elapsedTimePerY = static_cast<float>(totalTime) / static_cast<float>(barTopEdgePos);
	//// 経過時間(ms) = 曲の再生時間(ms) / 小節の末端までの変位 * カメラの下端座標
	//int elapsedTime = elapsedTimePerY * cameraDisplacement;

	//DrawFormatString(700, 275, GetColor(0, 255, 0), "経過時間(曲):%d", notesEditorMusic.GetElapsedTime());
	//DrawFormatString(700, 300, GetColor(0, 255, 0), "経過時間(計算):%d", elapsedTime);
	//DrawFormatString(700, 325, GetColor(0, 255, 0), "小節の末端座標:%d", barTopEdgePos);
	//DrawFormatString(700, 350, GetColor(0, 255, 0), "曲の総再生時間:%d", totalTime);
	//DrawFormatString(700, 375, GetColor(0, 255, 0), "カメラの下端座標:%f", cameraLowerEndPos);
	//DrawFormatString(700, 400, GetColor(0, 255, 0), "カメラの下端座標変位:%f", cameraDisplacement);
	//DrawFormatString(700, 425, GetColor(0, 255, 0), "1座標当たりの経過時間(ms):%f", elapsedTimePerY);
	//DrawFormatString(700, 450, GetColor(0, 255, 0), "誤差(ms):%d", notesEditorMusic.GetElapsedTime() - elapsedTime);

	//// 曲
	//NotesEditor::NotesEditorMusic& music = NotesEditor::NotesEditorMusic::Instance();
	//// 1小節の長さ
	//float barTimeLength = 60.f * 1000.f / static_cast<float>(music.GetBPM()) * 4.f;
	//note32TimeLength = barTimeLength / BarManager::MAXNOTENUM;
	//// 必要なライン数
	//int lineNum = static_cast<float>(totalTime) / note32TimeLength + 2;
	//DrawFormatString(700, 500, GetColor(0, 255, 0), "32音符の長さ:%f", note32TimeLength);
	//DrawFormatString(700, 525, GetColor(0, 255, 0), "総ライン数:%d", lineNum);

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
	PutNotes();
}

void NotesEditor::EditScene::OnMusicLoaded()
{
	editorSceneCanvas.OnMusicLoaded();
	// 曲
	NotesEditor::NotesEditorMusic& music = NotesEditor::NotesEditorMusic::Instance();
	// 曲の総再生時間
	float totalTime = static_cast<float>(music.GetTotalTime());
	// 曲のBPM
	float bpm = static_cast<float>(music.GetBPM());
	// 曲の拍子
	float beat = static_cast<float>(music.GetBeat());

	// 1小節の長さ
	float barTimeLength = 60.f * 1000.f / static_cast<float>(music.GetBPM()) * 4.f;
	// 最小音符の長さ
	float minimumNoteTimeLength = barTimeLength / BarManager::MAXNOTENUM;
	// 必要なライン数
	int lineNum = static_cast<float>(totalTime) / minimumNoteTimeLength + 2;
	//小節数の計算
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
