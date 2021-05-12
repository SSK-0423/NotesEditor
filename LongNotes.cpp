#include "LongNotes.hpp"
#include "DxLib.h"

//�N���X�ϐ����̉�
unsigned int LongNotes::color = GetColor(255,0,0);

LongNotes::LongNotes(float& x, float& y) noexcept {
	startNotes = nullptr;
	endNotes = nullptr;
	width = 20;
	height = 20;
	position.x = x;
	position.y = y;
	collisionPos.x = x;
	collisionPos.y = y;
}
LongNotes::LongNotes(Notes& start, Notes& end) noexcept {
	startNotes = &start;
	endNotes = &end;
}

LongNotes::~LongNotes() noexcept {
	delete[] startNotes;
	delete[] endNotes;
}

void LongNotes::Draw() noexcept {
	////�n�_�`��
	//startNotes->Draw();
	////�I�_�`��
	//endNotes->Draw();
	////�n�_�ƏI�_����Ōq��
	//DrawLine(startNotes->position.x, startNotes->position.y, endNotes->position.x, endNotes->position.y,color, 30);
	DrawBox(position.x - width / 2, position.y - height / 2,
		position.x + width / 2, position.y + height / 2,
		color, true);
}