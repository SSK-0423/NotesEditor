#include "DxLib.h"
#include "WindowSize.hpp"
#include "SceneManager.hpp"
#include "FPS.hpp"
#include "Editor.hpp"
#include "KeyInput.hpp"
#define NOTES_SIZE_WIDTH 79
#define NOTES_SIZE_HEIGHT 15


//ゲームループ
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//ウィンドウモード、初期化、裏画面設定
	SetGraphMode(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, 16);
	ChangeWindowMode(true), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(true);

	int handle = LoadGraph("image/ShortNotes02.png");
	int SUB = 25;
	int x = 472 - 82 * 2;
	int y = WINDOW_SIZE_HEIGHT / 2;
	int size = 15;
	SceneManager sceneManager;
	Fps fps;
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		sceneManager.Update();
		sceneManager.Draw();
		fps.Update();
		fps.Draw();

		//DrawModiGraph(
		//	WINDOW_SIZE_WIDTH / 2 + 2, WINDOW_SIZE_HEIGHT / 2 - NOTES_SIZE_HEIGHT,
		//	WINDOW_SIZE_WIDTH / 2 + NOTES_SIZE_WIDTH, WINDOW_SIZE_HEIGHT / 2 - NOTES_SIZE_HEIGHT,
		//	WINDOW_SIZE_WIDTH / 2 + NOTES_SIZE_WIDTH, WINDOW_SIZE_HEIGHT / 2 + NOTES_SIZE_HEIGHT,
		//	WINDOW_SIZE_WIDTH / 2 + 2, WINDOW_SIZE_HEIGHT / 2 + NOTES_SIZE_HEIGHT,
		//	handle, true);
		//if (Key[KEY_INPUT_F] == 1) {
		//	SUB += 1;
		//}
		//if (Key[KEY_INPUT_K] == 1) {
		//	SUB -= 1;
		//}
		//if (Key[KEY_INPUT_F] == 15) {
		//	SUB += 15;
		//}
		//if (Key[KEY_INPUT_K] == 15) {
		//	SUB -= 15;
		//}
		//DrawBox(WINDOW_SIZE_WIDTH / 2 - 10 - SUB, WINDOW_SIZE_HEIGHT / 2 - 15, WINDOW_SIZE_WIDTH / 2 + 10 - SUB, WINDOW_SIZE_HEIGHT / 2 + 15, GetColor(0, 255, 0), true);
		//DrawFormatString(800, 600, GetColor(0, 255, 0), "x:%d", WINDOW_SIZE_WIDTH / 2 - SUB);
		////for (int i = 0; i < 6; i++) {
		////	x += 82 * i;
		////	DrawBox(x - size,y - size, x + size, y + size,GetColor(0,255,0),true);
		////	x = 472 - 82 * 2;
		////}
	}
	DxLib_End();
	return 0;
}
//472  390 307 555 637 720