#include "ShortNotes.hpp"
#include "DxLib.h"
#include "WindowSize.hpp"
#include <math.h>

//クラス変数実体化
//int ShortNotes::clapHandle = LoadSoundMem("sounds/clap.ogg");

ShortNotes::ShortNotes(float& x, float& y) noexcept {
	clapHandle = LoadSoundMem("sounds/clap.ogg");
	color = GetColor(0, 255, 0);
	width = 80;
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
		PlaySoundMem(clapHandle, DX_PLAYTYPE_BACK);
	}
}

void ShortNotes::Draw() noexcept {
	DrawBox(position.x - width / 2, position.y - height / 2,
		position.x + width / 2, position.y + height / 2,
		color, true);
	
	DrawBox(position.x - width / 2, position.y - height / 2, position.x + width / 2, position.y + height / 2, GetColor(255, 0, 0), false);
	//	DrawCircle(position.x, position.y, 10, GetColor(255, 255, 255), true);
	//	DrawFormatString(800, 650, GetColor(0, 255, 0), "X:%f Y:%f", position.x, position.y);
}

void ShortNotes::SetColor(unsigned int c)
{
	color = c;
}

unsigned int ShortNotes::GetNotesColor() {
	return color;
}

//ハンドクラップ再生
void ShortNotes::PlayClap() noexcept {
	PlaySoundMem(clapHandle, DX_PLAYTYPE_BACK);
}