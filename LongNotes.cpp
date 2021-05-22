#include "LongNotes.hpp"
#include "DxLib.h"
#include <math.h>

//�N���X�ϐ����̉�
unsigned int LongNotes::color = GetColor(0, 255, 0);

LongNotes::LongNotes(ShortNotes& start) noexcept {
	startNotes = &start;
	endNotes = nullptr;
	width = 0;
	height = 0;
}

LongNotes::LongNotes(ShortNotes& start, ShortNotes& end) noexcept {
	startNotes = &start;
	endNotes = &end;
	//position�̐ݒ�
	position.x = startNotes->collisionPos.x;
	collisionPos.x = startNotes->collisionPos.x;
	position.y = (startNotes->collisionPos.y + endNotes->collisionPos.y) / 2;
	collisionPos.y = (startNotes->collisionPos.y + endNotes->collisionPos.y) / 2;
	//�T�C�Y�̐ݒ�
	width = 20;
	height = fabs(endNotes->collisionPos.y - startNotes->collisionPos.y);
}

LongNotes::~LongNotes() noexcept {
	delete[] startNotes;
	delete[] endNotes;
}

void LongNotes::SetStartNotes(ShortNotes& start) noexcept {
	startNotes = &start;
}

void LongNotes::SetEndNotes(ShortNotes& end) noexcept {
	endNotes = &end;
	//position�̐ݒ�
	position.x = startNotes->collisionPos.x;
	collisionPos.x = startNotes->collisionPos.x;
	position.y = (startNotes->collisionPos.y + endNotes->collisionPos.y) / 2;
	collisionPos.y = (startNotes->collisionPos.y + endNotes->collisionPos.y) / 2;
	//�T�C�Y�̐ݒ�
	width = 20;
	height = fabs(fabs(endNotes->position.y) - fabs(startNotes->position.y));
}

void LongNotes::SetObjSize(int w, int h) noexcept {
	width = w;
	height = h;
}

void LongNotes::Update() noexcept {
	startNotes->SetPosition(position.x, position.y + height / 2);
	endNotes->SetPosition(position.x, position.y - height / 2);
}

void LongNotes::Draw() noexcept {

	//�n�_�`��
	startNotes->Draw();
	//�I�_�`��
	endNotes->Draw();
	//�n�_�ƏI�_����Ōq��
	DrawLine(startNotes->position.x, startNotes->position.y, endNotes->position.x, endNotes->position.y, color, 20);

	/*DrawBox(position.x - width / 2, position.y - height / 2,
		position.x + width / 2, position.y + height / 2,
		color, true);*/
}
