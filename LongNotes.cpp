#include "LongNotes.hpp"
#include "DxLib.h"

//クラス変数実体化
unsigned int LongNotes::color = GetColor(255,0,0);

LongNotes::LongNotes(ShortNotes& start) noexcept {
	startNotes = &start;
	endNotes = nullptr;
	width = 20;
	height = 20;
}

LongNotes::LongNotes(ShortNotes& start, ShortNotes& end) noexcept {
	startNotes = &start;
	endNotes = &end;
}

LongNotes::~LongNotes() noexcept {
	delete[] startNotes;
	delete[] endNotes;
}

void LongNotes::AddEndNotes(ShortNotes& end) noexcept {
	endNotes = &end;
}

void LongNotes::SetObjSize(int w, int h) noexcept {
	width = w;
	height = h;
}

void LongNotes::Draw() noexcept {

	//始点描画
	startNotes->Draw();
	//終点描画
	endNotes->Draw();
	//始点と終点を線で繋ぐ
	DrawLine(startNotes->position.x, startNotes->position.y, endNotes->position.x, endNotes->position.y,color, 30);
	
	/*DrawBox(position.x - width / 2, position.y - height / 2,
		position.x + width / 2, position.y + height / 2,
		color, true);*/

}
