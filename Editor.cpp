#include "Editor.hpp"
#include "WindowSize.hpp"
#include "OpenFileExplorer.hpp"
#include "Delegate.hpp"
#include "DxLib.h"
#include "Mouse.hpp"
#include "KeyInput.hpp"
#include <string>
#include <Windows.h>

Editor::Editor(ISceneChanger* changer) : BaseScene(changer), speed(1), count(0), camera(objList) {
	fontHandle = CreateFontToHandle("font1", 10, 1, DX_FONTTYPE_ANTIALIASING);
	backgroungHandle = LoadGraph("image/背景.jpg");
	laneHandle = LoadGraph("image/Lane.png");

	musicInfoHandle = LoadGraph("image/MUSIC_NAME_BPM.png");
	text.SetHandle(musicInfoHandle);
	text.SetColor(0, 0, 0);
	InitBarManager();
	InitButton();
}

// 小節数オブジェクトの生成
void Editor::MakeBar() noexcept {
	camera.DeleteObj();
	barManager.DeleteObj();

	//小節数の計算
	//ループまでの間にも小節線を描画するために+2をする
	int bar_num = music.GetTotalTime() / 1000 * music.GetBPM() / (60 * music.GetBeat()) + 2;
	camera.SetMinPosition(WINDOW_SIZE_WIDTH / 2, -WINDOW_SIZE_HEIGHT * bar_num);
	camera.SetMaxPosition(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2);

	barManager.MakeBar(objList, bar_num);
}

void Editor::Initialize() noexcept {}
void Editor::Finalize() noexcept {}

void Editor::Update() noexcept {
	//曲が読み込まれたら小節線を作成する
	if (music.IsMusicLoad()) {
		MakeBar();
		music.ChangeIsMusicLoad();
		InitTextBox();
		CalcFrameMove();
	}
	KeyInput();
	ScrollCamera();
	UpdateButton();
	InitTextBox();
	barManager.Update();
	camera.Update();
}

//描画
void Editor::Draw() noexcept {
	DrawGraph(0, 0, backgroungHandle, true);
	DrawRotaGraph(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2, 1.01, 0, laneHandle, true, false);
	DrawButton();
	text.Draw();
	camera.Draw();
	barManager.Draw();
	DebugDraw();
}

void Editor::DrawButton() noexcept {
	for (int i = 0; i < BUTTON_NUM; i++) {
		button[i].Draw();
	}
}

void Editor::UpdateButton() noexcept {
	//Buttonのアップデート
	for (int i = 0; i < BUTTON_NUM; i++) {
		button[i].Update();
	}
}

//ボタンの初期化
void Editor::InitButton() noexcept {
	button = new Button[BUTTON_NUM];

	SetButtonImage();
	SetButtonPos();
	SetClickEventFunc();
}

//ボタンの画像セット
void Editor::SetButtonImage() noexcept {
	button[BUTTON_SHORT].SetImageHandle("image/SHORT.png");
	button[BUTTON_LONG].SetImageHandle("image/LONG.png");
	button[BUTTON_SLIDE].SetImageHandle("image/SLIDE.png");
	button[BUTTON_PLAY].SetImageHandle("image/PLAY.png");
	button[BUTTON_PLAY].SetImageHandle("image/STOP.png");
	button[BUTTON_RESTART].SetImageHandle("image/RESTART.png");
	button[BUTTON_LOADMUSIC].SetImageHandle("image/LOADMUISC.png");
	button[BUTTON_CHANGEBAR].SetImageHandle("image/CHANGE_BAR.png");
	button[BUTTON_CHANGEBAR4].SetImageHandle("image/CHANGE_BAR4.png");
	button[BUTTON_CHANGEBAR8].SetImageHandle("image/CHANGE_BAR8.png");
	button[BUTTON_CHANGEBAR16].SetImageHandle("image/CHANGE_BAR16.png");
	button[BUTTON_CHANGEBAR32].SetImageHandle("image/CHANGE_BAR32.png");
	button[BUTTON_LOAD].SetImageHandle("image/LOAD.png");
	button[BUTTON_SAVE].SetImageHandle("image/SAVE.png");
}
//ボタンの位置セット
void Editor::SetButtonPos() noexcept {
	button[BUTTON_SHORT].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_LONG].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_SLIDE].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_PLAY].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 2, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_RESTART].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 2, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_LOADMUSIC].SetButtonInfo(BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 3, BUTTON_SIZE_WIDTH * 2, BUTTON_SIZE2_HEIGHT);
	button[BUTTON_CHANGEBAR].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 4, BUTTON_SIZE_WIDTH, BUTTON_SIZE2_HEIGHT);
	button[BUTTON_CHANGEBAR4].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 4, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_CHANGEBAR8].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 5, BUTTON_SIZE_WIDTH, BUTTON_SIZE2_HEIGHT);
	button[BUTTON_CHANGEBAR16].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 5, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_CHANGEBAR32].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 6, BUTTON_SIZE_WIDTH, BUTTON_SIZE2_HEIGHT);
	button[BUTTON_LOAD].SetButtonInfo(BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 7, BUTTON_SIZE_WIDTH * 2, BUTTON_SIZE2_HEIGHT);
	button[BUTTON_SAVE].SetButtonInfo(BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 8, BUTTON_SIZE_WIDTH * 2, BUTTON_SIZE2_HEIGHT);
}

//ボタンのイベント関数セット
void Editor::SetClickEventFunc() noexcept {
	//曲の再生停止
	DelegateBase<void(void)>* playMusic = Delegate<Music, void(void)>::createDelegator(&music, &Music::PlayMusic);
	//曲を始めから再生
	DelegateBase<void(void)>* restartMusic = Delegate<Music, void(void)>::createDelegator(&music, &Music::RestartMusic);
	//曲の読込
	DelegateBase<void(void)>* loadMusic = Delegate<Music, void(void)>::createDelegator(&music, &Music::LoadMusic);
	//譜面データ読み込み
	//DelegateBase<void(void)>* loadJson = Delegate<Music, void(void)>::createDelegator(&music, &Music::loadJson);
	//譜面データ書き出し
	//DelegateBase<void(void)>* saveJson = Delegate<Music, void(void)>::createDelegator(&music, &Music::saveJson);

	//小節線変更
	DelegateBase<void(void)>* change_bar = Delegate<BarManager, void(void)>::createDelegator(&barManager, &BarManager::ChangeHandle);
	DelegateBase<void(void)>* change_bar4 = Delegate<BarManager, void(void)>::createDelegator(&barManager, &BarManager::ChangeHandle4);
	DelegateBase<void(void)>* change_bar8 = Delegate<BarManager, void(void)>::createDelegator(&barManager, &BarManager::ChangeHandle8);
	DelegateBase<void(void)>* change_bar16 = Delegate<BarManager, void(void)>::createDelegator(&barManager, &BarManager::ChangeHandle16);
	DelegateBase<void(void)>* change_bar32 = Delegate<BarManager, void(void)>::createDelegator(&barManager, &BarManager::ChangeHandle32);

	//押下時の関数セット
	button[BUTTON_PLAY].SetEventFunction(playMusic);
	button[BUTTON_RESTART].SetEventFunction(restartMusic);
	button[BUTTON_LOADMUSIC].SetEventFunction(loadMusic);
	button[BUTTON_CHANGEBAR].SetEventFunction(change_bar);
	button[BUTTON_CHANGEBAR4].SetEventFunction(change_bar4);
	button[BUTTON_CHANGEBAR8].SetEventFunction(change_bar8);
	button[BUTTON_CHANGEBAR16].SetEventFunction(change_bar16);
	button[BUTTON_CHANGEBAR32].SetEventFunction(change_bar32);
}

void Editor::InitBarManager() noexcept {
}


void Editor::DebugDraw() noexcept {
	int bar_num = (music.GetTotalTime() / 1000) * music.GetBPM() / (60 * music.GetBeat());
	DrawFormatString(800, 50, GetColor(0, 255, 0), "%dフレーム", count);
	DrawFormatString(800, 100, GetColor(0, 255, 0), "経過時間:%f", music.GetElapsedTime() / 1000.0f);
	char buff[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, buff);
	DrawFormatString(0, 740, GetColor(0, 255, 0), "%s", buff);
}

void Editor::InitTextBox() noexcept {
	//曲名とBPMの
	std::string str = music.GetName();
	text.SetText(str);
	str = "BPM:";
	str += std::to_string((int)music.GetBPM());
	text.SetText(str);
}

void Editor::ScrollCamera() noexcept {
	//曲が再生されたら自動スクロール開始
	if (music.IsPlay()) {
		camera.SetPosition(WINDOW_SIZE_WIDTH / 2, -frame_move * music.GetElapsedTime() / 1000.0f * 60.0f + WINDOW_SIZE_HEIGHT / 2);
	}
}

void Editor::KeyInput() noexcept {
	if (Key[KEY_INPUT_D] == 1) {
		DeleteObj();
	}
	Mouse::Instance()->Update();
	if (Mouse::Instance()->GetPressingCount(Mouse::LEFT_CLICK) == 1) {
		int x, y;
		GetMousePoint(&x, &y);
		if (x >= 1024 / 2 - 1024 / 4 && x <= 1024 / 2 + 1024 / 4) {
			PutNotes();
		}
	}
}

void Editor::CalcFrameMove() noexcept {
	// 1小節の縦幅 / ((60 * beat * speed / bpm)  * 60) = 1フレームの移動幅
	frame_move = WINDOW_SIZE_HEIGHT / (music.GetBeat() * (60 / music.GetBPM()) * 60);
}

void Editor::AddObject(GameObject& obj) noexcept {
	objList.push_back(&obj);
}

void Editor::PutNotes() noexcept {
	//何小節目は判定
	//何分目か判定
	//レーン判定
	barManager.CheckBarCollision();
	//設置
	//NotesManager.AddNotes();
}

void Editor::DeleteObj() noexcept {
	camera.DeleteObj();
	barManager.DeleteObj();
	for (auto i : objList) {
		delete[] i;
		objList.clear();
	}
}