#include "LongNotesCreator.hpp"
#include "LongNotes.hpp"
#include "Mouse.hpp"
#include <math.h>
LongNotesCreator::LongNotesCreator(BarManager& barManager) noexcept {
	this->barManager = &barManager;
}

//ロングノーツの生成
Notes* LongNotesCreator::CreateNotes(float& x, float& y) noexcept {
	//始点ノーツ生成
	ShortNotes* start = new ShortNotes(x, y);
	//始点を追加してロングノーツ生成
	LongNotes* longNotes = new LongNotes((ShortNotes&)*start);
	//終端ノーツを設置したかどうか
	bool isPut = false;
	//終端ノーツを設置するまでループ
	while (!isPut) {
		Mouse::Instance()->Update();
		if (Mouse::Instance()->GetPressingCount(Mouse::LEFT_CLICK) == 1) {
			int x, y;
			GetMousePoint(&x, &y);
			if (x >= 1024 / 2 - 1024 / 4 && x <= 1024 / 2 + 1024 / 4) {
				float putPosX, putPosY;
				//ノーツの設置位置を決定
				barManager->DecidePutPos(putPosX, putPosY);
				if (putPosX != start->position.x) {
					putPosX = start->position.x;
				}
				ShortNotes* end = new ShortNotes(putPosX,putPosY);
				longNotes->AddEndNotes(*end);
				longNotes->SetObjSize(30, (int)fabs(start->position.y - end->position.y));
				isPut = true;
			}
		}
	}
	return longNotes;
}