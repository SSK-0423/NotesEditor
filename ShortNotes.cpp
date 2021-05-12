#include "ShortNotes.hpp"
#include "DxLib.h"

//�N���X�ϐ����̉�
int ShortNotes::clapHandle = LoadSoundMem("sounds/clap.ogg");

ShortNotes::ShortNotes(float& x, float& y) noexcept{
	width = 20;
	height = 20;
	position.x = x;
	position.y = y;
	collisionPos.x = x;
	collisionPos.y = y;
}
ShortNotes::~ShortNotes() noexcept {

}
void ShortNotes::Draw() noexcept {
	DrawBox(position.x - width / 2, position.y - height / 2,
		position.x + width / 2, position.y + height / 2,
		GetColor(0, 255, 0), true);
}

//�n���h�N���b�v�Đ�
void ShortNotes::PlayClap() noexcept {
	PlaySoundMem(clapHandle,DX_PLAYTYPE_BACK);
}