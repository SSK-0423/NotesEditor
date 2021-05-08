#include "DxLib.h"
#include "WindowSize.hpp"
#include "SceneManager.hpp"
#include "FPS.hpp"
#include "Editor.hpp"
#define NOTES_SIZE_WIDTH 79
#define NOTES_SIZE_HEIGHT 15

//ゲームループ
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//ウィンドウモード、初期化、裏画面設定
	SetGraphMode(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, 16);
	ChangeWindowMode(true), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(true);

	int handle = LoadGraph("image/ShortNotes02.png");

	SceneManager sceneManager;
	Fps fps;
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		sceneManager.Update();
		sceneManager.Draw();
		fps.Update();
		fps.Draw();
		/*DrawModiGraph(
			WINDOW_SIZE_WIDTH / 2 + 2, WINDOW_SIZE_HEIGHT / 2 - NOTES_SIZE_HEIGHT,
			WINDOW_SIZE_WIDTH / 2 + 2 + NOTES_SIZE_WIDTH, WINDOW_SIZE_HEIGHT / 2 - NOTES_SIZE_HEIGHT,
			WINDOW_SIZE_WIDTH / 2 + 2 + NOTES_SIZE_WIDTH, WINDOW_SIZE_HEIGHT / 2 + NOTES_SIZE_HEIGHT,
			WINDOW_SIZE_WIDTH / 2 + 2, WINDOW_SIZE_HEIGHT / 2 + NOTES_SIZE_HEIGHT,
			handle, true);
		DrawModiGraph(
			WINDOW_SIZE_WIDTH / 2 - NOTES_SIZE_WIDTH, WINDOW_SIZE_HEIGHT / 2 - NOTES_SIZE_HEIGHT,
			WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2 - NOTES_SIZE_HEIGHT,
			WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2 + NOTES_SIZE_HEIGHT,
			WINDOW_SIZE_WIDTH / 2 - NOTES_SIZE_WIDTH, WINDOW_SIZE_HEIGHT / 2 + NOTES_SIZE_HEIGHT,
			handle, true);*/

	}
	DxLib_End();
	return 0;
}