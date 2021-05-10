#include "LongNotes.hpp"
#include "DxLib.h"

//�N���X�ϐ����̉�
unsigned int LongNotes::color = GetColor(128,128,128);

LongNotes::LongNotes() noexcept {
	startNotes = nullptr;
	endNotes = nullptr;
}

LongNotes::LongNotes(Notes& start, Notes& end) {
	startNotes = &start;
	endNotes = &end;
}

LongNotes::~LongNotes() noexcept {
	delete[] startNotes;
	delete[] endNotes;
}

void LongNotes::Draw() noexcept {
	//�n�_�`��
	startNotes->Draw();
	//�I�_�`��
	endNotes->Draw();
	//�n�_�ƏI�_����Ōq��
	DrawLine(startNotes->position.x, startNotes->position.y, endNotes->position.x, endNotes->position.y,color, 30);
}