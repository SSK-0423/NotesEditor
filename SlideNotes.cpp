#include "SlideNotes.hpp"
#include "DxLib.h"
SlideNotes::SlideNotes(float& x, float& y) noexcept {
	width = 20;
	height = 20;
	position.x = x;
	position.y = y;
	collisionPos.x = x;
	collisionPos.y = y;
}

SlideNotes::~SlideNotes() noexcept {
	for (auto obj : notes) {
		delete[] obj;
	}
	notes.clear();
}

void SlideNotes::Draw() noexcept {
	DrawBox(position.x - width / 2, position.y - height / 2,
		position.x + width / 2, position.y + height / 2,
		GetColor(0, 0, 255), true);
}