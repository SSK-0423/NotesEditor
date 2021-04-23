#include "Editor.hpp"
#include "WindowSize.hpp"
#include "OpenFileExplorer.hpp"
#include "Delegate.hpp"
#include "Bar.hpp"
#include "Camera2D.hpp"
#include "DxLib.h"
#include <string>
#include <Windows.h>

Editor::Editor(ISceneChanger* changer) : BaseScene(changer), speed(1), count(0) {
	fontHandle = CreateFontToHandle("font1", 10, 1, DX_FONTTYPE_ANTIALIASING);
	backgroungHandle = LoadGraph("image/�w�i.jpg");
	laneHandle = LoadGraph("image/Lane.png");
	//lineHandle = LoadGraph("image/�m�[�c���C��.png");

	//���ߐ��摜�n���h���̏�����
	barHandle = LoadGraph("image/Bar.png");
	bar4Handle = LoadGraph("image/Bar4.png");
	bar8Handle = LoadGraph("image/Bar8.png");
	bar16Handle = LoadGraph("image/Bar16.png");
	bar32Handle = LoadGraph("image/Bar32.png");

	musicInfoHandle = LoadGraph("image/MUSIC_NAME_BPM.png");
	text.SetImage(musicInfoHandle);
	text.SetColor(0, 0, 0);

	//���ߐ��摜�̃Z�b�g
	barController.SetHandle(barHandle);
	barController.SetHandle(bar4Handle);
	barController.SetHandle(bar8Handle);
	barController.SetHandle(bar16Handle);
	barController.SetHandle(bar32Handle);
	InitButton();
}

// ���ߐ��I�u�W�F�N�g�̐���
void Editor::MakeBar() {
	camera.DeleteObj();
	barController.DeleteObj();
	//���ߐ��̌v�Z
	//���[�v�܂ł̊Ԃɂ����ߐ���`�悷�邽�߂�+2������
	int bar_num = music.GetTotalTime() / 1000 * music.bpm / (60 * music.beat) + 2;
	camera.SetMinPosition(WINDOW_SIZE_WIDTH / 2, -WINDOW_SIZE_HEIGHT * bar_num);
	camera.SetMaxPosition(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2);
	//���ߐ��I�u�W�F�N�g�̐���
	for (int i = 0; i < bar_num + 2; i++) {
		Bar* bar = new Bar(bar32Handle, i);
		camera.SetObject(bar);
		barController.SetObject(bar);
	}
}

void Editor::DrawBar() {}
void Editor::Initialize() {}
void Editor::Finalize() {}

void Editor::Update() {
	//�Ȃ��ǂݍ��܂ꂽ�珬�ߐ����쐬����
	if (music.isMusicLoad) {
		MakeBar();
		music.isMusicLoad = false;
	}
	//Button�̃A�b�v�f�[�g
	for (int i = 0; i < BUTTON_NUM; i++) {
		button[i].Update();
	}
	//
	if (CheckHitKey(KEY_INPUT_D) != 0) {
		//GameObject�̃������J��
		camera.DeleteObj();
	}

	//�Ȗ���BPM�̕\��
	std::string str = music.name;
	text.SetText(str.c_str());
	str = "BPM:";
	str += std::to_string((int)music.bpm);
	text.SetText(str.c_str());

	if (music.isPlay) {
		// 1���߂̏c�� / ((60 * beat * speed / bpm)  * 60) = 1�t���[���̈ړ���
		float frame_move = WINDOW_SIZE_HEIGHT / (music.beat * (60 / music.bpm) * 60);
		camera.SetPosition(WINDOW_SIZE_WIDTH / 2, -frame_move * music.GetElapsedTime() / 1000.0f * 60.0f + WINDOW_SIZE_HEIGHT / 2);
	}

	// 1�������ꂽ��
	if (CheckHitKey(KEY_INPUT_1) != 0) {
	}
	// 2�������ꂽ��
	if (CheckHitKey(KEY_INPUT_2) != 0) {
	}
	// 3�������ꂽ��
	if (CheckHitKey(KEY_INPUT_3) != 0) {
	}

	barController.Update();
	camera.Update();
}

//�`��
void Editor::Draw() {
	int bar_num = (music.GetTotalTime() / 1000) * music.bpm / (60 * music.beat);
	DrawGraph(0, 0, backgroungHandle, true);
	DrawRotaGraph(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2, 1.01, 0, laneHandle, true, false);
	//DrawRotaGraph(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2, 1.01, 0, lineHandle, true, false);
	DrawBar();
	DrawButton();
	//DrawRotaGraph(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2, 1.01, 0, barLineHandle, true, false);
	//DrawModiGraph(10, 10, BUTTON_SIZE_WIDTH * 2 + ADD / 2, 10, BUTTON_SIZE_WIDTH * 2 + ADD / 2, BUTTON_SIZE_HEIGHT*2, 10, BUTTON_SIZE_HEIGHT, test_handle, true);
	//DrawFormatString(512, 0, GetColor(0, 255, 0), "���ߐ�:%d", bar_num);
	//DrawFormatStringToHandle(BUTTON_SIZE_WIDTH/2, 10, GetColor(0, 0, 255),fontHandle, "BPM:%6.2f", music.bpm);
	/*DrawFormatString(700, 20, GetColor(0, 255, 0), "BEAT:%d", music.beat);
	DrawFormatString(700, 40, GetColor(0, 255, 0), "NAME:%s", music.name.c_str());
	DrawFormatString(700, 60, GetColor(0, 255, 0), "musicHandle:%d", music.musicHandle);
	*/
	DrawFormatString(800, 50, GetColor(0, 255, 0), "%d�t���[��", count);
	//float frame_move = 780 / ((3600 * music.beat * 1) / music.bpm);
	DrawFormatString(800, 100, GetColor(0, 255, 0), "�o�ߎ���:%f", music.GetElapsedTime() / 1000.0f);
	barController.Draw();
	text.Draw();
	camera.Draw();
	char buff[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, buff);
	DrawFormatString(0, 740, GetColor(0, 255, 0), "%s", buff);

}

void Editor::DrawButton() {
	for (int i = 0; i < BUTTON_NUM; i++) {
		button[i].Draw();
	}
}

void Editor::InitButton() {

	////�{�^���摜�̃n���h��
	//int* imageHandle = new int[BUTTON_NUM];
	//imageHandle[BUTTON_SHORT] = LoadGraph("image/SHORT.png");
	//imageHandle[BUTTON_LONG] = LoadGraph("image/LONG.png");
	//imageHandle[BUTTON_SLIDE] = LoadGraph("image/SLIDE.png");
	//imageHandle[BUTTON_PLAY] = LoadGraph("image/PLAY.png");
	//imageHandle[BUTTON_STOP] = LoadGraph("image/STOP.png");
	//imageHandle[BUTTON_RESTART] = LoadGraph("image/RESTART.png");
	//imageHandle[BUTTON_LOADMUSIC ] = LoadGraph("image/LOADMUSIC.png");
	//imageHandle[BUTTON_LOAD] = LoadGraph("image/LOAD.png");
	//imageHandle[BUTTON_SAVE] = LoadGraph("image/SAVE.png");

	//�{�^���̏������Ɣz�u
	button = new Button[BUTTON_NUM];

	button[BUTTON_SHORT].SetImageHandle("image/SHORT.png");
	button[BUTTON_SHORT].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_LONG].SetImageHandle("image/LONG.png");
	button[BUTTON_LONG].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_SLIDE].SetImageHandle("image/SLIDE.png");
	button[BUTTON_SLIDE].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_PLAY].SetImageHandle("image/PLAY.png");
	button[BUTTON_PLAY].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 2, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_PLAY].SetImageHandle("image/STOP.png");
	button[BUTTON_RESTART].SetImageHandle("image/RESTART.png");
	button[BUTTON_RESTART].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 2, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_LOADMUSIC].SetImageHandle("image/LOADMUISC.png");
	button[BUTTON_LOADMUSIC].SetButtonInfo(BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 3, BUTTON_SIZE_WIDTH * 2, BUTTON_SIZE2_HEIGHT);
	button[BUTTON_CHANGEBAR].SetImageHandle("image/CHANGE_BAR.png");
	button[BUTTON_CHANGEBAR].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 4, BUTTON_SIZE_WIDTH, BUTTON_SIZE2_HEIGHT);
	button[BUTTON_CHANGEBAR4].SetImageHandle("image/CHANGE_BAR4.png");
	button[BUTTON_CHANGEBAR4].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 4, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_CHANGEBAR8].SetImageHandle("image/CHANGE_BAR8.png");
	button[BUTTON_CHANGEBAR8].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 5, BUTTON_SIZE_WIDTH, BUTTON_SIZE2_HEIGHT);
	button[BUTTON_CHANGEBAR16].SetImageHandle("image/CHANGE_BAR16.png");
	button[BUTTON_CHANGEBAR16].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 5, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT);
	button[BUTTON_CHANGEBAR32].SetImageHandle("image/CHANGE_BAR32.png");
	button[BUTTON_CHANGEBAR32].SetButtonInfo(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 6, BUTTON_SIZE_WIDTH, BUTTON_SIZE2_HEIGHT);
	button[BUTTON_LOAD].SetImageHandle("image/LOAD.png");
	button[BUTTON_LOAD].SetButtonInfo(BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 7, BUTTON_SIZE_WIDTH * 2, BUTTON_SIZE2_HEIGHT);
	button[BUTTON_SAVE].SetImageHandle("image/SAVE.png");
	button[BUTTON_SAVE].SetButtonInfo(BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 8, BUTTON_SIZE_WIDTH * 2, BUTTON_SIZE2_HEIGHT);

	//�C�x���g�֐��̐ݒ�
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
	DelegateBase<void(void)>* change_bar = Delegate<BarController, void(void)>::createDelegator(&barController, &BarController::ChangeHandle);
	DelegateBase<void(void)>* change_bar4 = Delegate<BarController, void(void)>::createDelegator(&barController, &BarController::ChangeHandle4);
	DelegateBase<void(void)>* change_bar8 = Delegate<BarController, void(void)>::createDelegator(&barController, &BarController::ChangeHandle8);
	DelegateBase<void(void)>* change_bar16 = Delegate<BarController, void(void)>::createDelegator(&barController, &BarController::ChangeHandle16);
	DelegateBase<void(void)>* change_bar32 = Delegate<BarController, void(void)>::createDelegator(&barController, &BarController::ChangeHandle32);
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