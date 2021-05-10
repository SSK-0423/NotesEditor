#include "LongNotes.hpp"
#include "DxLib.h"

//クラス変数実体化
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
	//始点描画
	startNotes->Draw();
	//終点描画
	endNotes->Draw();
	//始点と終点を線で繋ぐ
	DrawLine(startNotes->position.x, startNotes->position.y, endNotes->position.x, endNotes->position.y,color, 30);
}