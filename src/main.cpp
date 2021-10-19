#include "Application.hpp"
#include "WindowSize.hpp"
#include "DxLib.h"

//ゲームループ
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	SetWindowText("NotesEditor");
	SetGraphMode(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, 16);
	//ウィンドウモード、初期化、裏画面設定
	ChangeWindowMode(true), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	SetDrawMode(DX_DRAWMODE_NEAREST);
	SetAlwaysRunFlag(true);
	Application game;
	game.MainLoop();
	DxLib_End();
	return 0;
}
//472  390 307 555 637 720