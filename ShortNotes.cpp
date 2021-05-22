#include "ShortNotes.hpp"
#include "DxLib.h"
#include "WindowSize.hpp"
#include <math.h>

//クラス変数実体化
//int ShortNotes::clapHandle = LoadSoundMem("sounds/clap.ogg");

ShortNotes::ShortNotes(float& x, float& y) noexcept{
	clapHandle = LoadSoundMem("sounds/clap.ogg");
	width = 20;
	height = 20;
	position.x = x;
	position.y = y;
	collisionPos.x = x;
	collisionPos.y = y;
}
ShortNotes::~ShortNotes() noexcept {

}
void ShortNotes::Update() noexcept {
	if (fabs(position.y - WINDOW_SIZE_HEIGHT) <= 5) {
		PlaySoundMem(clapHandle,DX_PLAYTYPE_BACK);
	}
}
void ShortNotes::Draw() noexcept {
	DrawBox(position.x - width / 2, position.y - height / 2,
		position.x + width / 2, position.y + height / 2,
		GetColor(0, 255, 0), true);
	//DrawFormatString(800, 500, GetColor(0, 255, 0), "X:%f Y:%f", position.x, position.y);
}

//ハンドクラップ再生
void ShortNotes::PlayClap() noexcept {
	PlaySoundMem(clapHandle,DX_PLAYTYPE_BACK);
}