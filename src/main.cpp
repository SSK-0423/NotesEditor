#include "Application.hpp"
#include "WindowSize.hpp"
#include "DxLib.h"

//�Q�[�����[�v
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	//�E�B���h�E���[�h�A�������A����ʐݒ�
	SetGraphMode(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, 16);
	ChangeWindowMode(true), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	SetDrawMode(DX_DRAWMODE_NEAREST);
	SetAlwaysRunFlag(true);
	SetWindowText("NotesEditor");
	Application game;
	game.MainLoop();
	DxLib_End();
	return 0;
}
//472  390 307 555 637 720