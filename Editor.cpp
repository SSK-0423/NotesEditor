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
	backgroungHandle = LoadGraph("image/�w�i.jpg");
	laneHandle = LoadGraph("image/Lane.png");

	musicInfoHandle = LoadGraph("image/MUSIC_NAME_BPM.png");
	text.SetHandle(musicInfoHandle);
	text.SetColor(0, 0, 0);
	InitBarManager();
	InitButton();
}

// ���ߐ��I�u�W�F�N�g�̐���
void Editor::MakeBar() noexcept {
	camera.DeleteObj();
	barManager.DeleteObj();

	//���ߐ��̌v�Z
	//���[�v�܂ł̊Ԃɂ����ߐ���`�悷�邽�߂�+2������
	int bar_num = music.GetTotalTime() / 1000 * music.GetBPM() / (60 * music.GetBeat()) + 2;
	camera.SetMinPosition(WINDOW_SIZE_WIDTH / 2, -WINDOW_SIZE_HEIGHT * bar_num);
	camera.SetMaxPosition(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2);

	barManager.MakeBar(objList, bar_num);
}

void Editor::Initialize() noexcept {}
void Editor::Finalize() noexcept {}

void Editor::Update() noexcept {
	//�Ȃ��ǂݍ��܂ꂽ�珬�ߐ����쐬����
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

//�`��
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
	//Button�̃A�b�v�f�[�g
	for (int i = 0; i < BUTTON_NUM; i++) {
		button[i].Update();
	}
}

//�{�^���̏�����
void Editor::InitButton() noexcept {
	button = new Button[BUTTON_NUM];

	SetButtonImage();
	SetButtonPos();
	SetClickEventFunc();
}

//�{�^���̉摜�Z�b�g
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
//�{�^���̈ʒu�Z�b�g
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

//�{�^���̃C�x���g�֐��Z�b�g
void Editor::SetClickEventFunc() noexcept {
	//�Ȃ̍Đ���~
	DelegateBase<void(void)>* playMusic = Delegate<Music, void(void)>::createDelegator(&music, &Music::PlayMusic);
	//�Ȃ��n�߂���Đ�
	DelegateBase<void(void)>* restartMusic = Delegate<Music, void(void)>::createDelegator(&music, &Music::RestartMusic);
	//�Ȃ̓Ǎ�
	DelegateBase<void(void)>* loadMusic = Delegate<Music, void(void)>::createDelegator(&music, &Music::LoadMusic);
	//���ʃf�[�^�ǂݍ���
	//DelegateBase<void(void)>* loadJson = Delegate<Music, void(void)>::createDelegator(&music, &Music::loadJson);
	//���ʃf�[�^�����o��
	//DelegateBase<void(void)>* saveJson = Delegate<Music, void(void)>::createDelegator(&music, &Music::saveJson);

	//���ߐ��ύX
	DelegateBase<void(void)>* change_bar = Delegate<BarManager, void(void)>::createDelegator(&barManager, &BarManager::ChangeHandle);
	DelegateBase<void(void)>* change_bar4 = Delegate<BarManager, void(void)>::createDelegator(&barManager, &BarManager::ChangeHandle4);
	DelegateBase<void(void)>* change_bar8 = Delegate<BarManager, void(void)>::createDelegator(&barManager, &BarManager::ChangeHandle8);
	DelegateBase<void(void)>* change_bar16 = Delegate<BarManager, void(void)>::createDelegator(&barManager, &BarManager::ChangeHandle16);
	DelegateBase<void(void)>* change_bar32 = Delegate<BarManager, void(void)>::createDelegator(&barManager, &BarManager::ChangeHandle32);

	//�������̊֐��Z�b�g
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
	DrawFormatString(800, 50, GetColor(0, 255, 0), "%d�t���[��", count);
	DrawFormatString(800, 100, GetColor(0, 255, 0), "�o�ߎ���:%f", music.GetElapsedTime() / 1000.0f);
	char buff[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, buff);
	DrawFormatString(0, 740, GetColor(0, 255, 0), "%s", buff);
}

void Editor::InitTextBox() noexcept {
	//�Ȗ���BPM��
	std::string str = music.GetName();
	text.SetText(str);
	str = "BPM:";
	str += std::to_string((int)music.GetBPM());
	text.SetText(str);
}

void Editor::ScrollCamera() noexcept {
	//�Ȃ��Đ����ꂽ�玩���X�N���[���J�n
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
	// 1���߂̏c�� / ((60 * beat * speed / bpm)  * 60) = 1�t���[���̈ړ���
	frame_move = WINDOW_SIZE_HEIGHT / (music.GetBeat() * (60 / music.GetBPM()) * 60);
}

void Editor::AddObject(GameObject& obj) noexcept {
	objList.push_back(&obj);
}

void Editor::PutNotes() noexcept {
	//�����ߖڂ͔���
	//�����ڂ�����
	//���[������
	barManager.CheckBarCollision();
	//�ݒu
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