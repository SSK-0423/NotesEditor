#include "DxLib.h"
#include "WindowSize.hpp"
#include "SceneManager.hpp"
#include "FPS.hpp"
#include "Editor.hpp"
#include "KeyInput.hpp"
#define NOTES_SIZE_WIDTH 79
#define NOTES_SIZE_HEIGHT 15

//�Q�[�����[�v
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//�E�B���h�E���[�h�A�������A����ʐݒ�
	SetGraphMode(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, 16);
	ChangeWindowMode(true), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(true);

	SceneManager sceneManager;
	Fps fps;
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		sceneManager.Update();
		sceneManager.Draw();
		fps.Update();
		fps.Draw();
	}
	DxLib_End();
	return 0;
}
//472  390 307 555 637 720