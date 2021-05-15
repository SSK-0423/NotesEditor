#include "LongNotesCreator.hpp"

//クラス変数実体化
bool LongNotesCreator::isStart = true;

LongNotesCreator::LongNotesCreator() noexcept {
	startNotes = nullptr;
	endNotes = nullptr;
}

//ロングノーツの生成
//void LongNotesCreator::CreateNotes(float& x, float& y) noexcept {
//
//	if (isStart) {
//		startNotes = new ShortNotes(x, y);
//		longNotes->SetStartNotes(*startNotes);
//	}
//	else {
//		endNotes = new ShortNotes(x, y);
//		longNotes->SetEndNotes(*endNotes);
//	}
//}

Notes* LongNotesCreator::CreateNotes(float& x, float& y) noexcept {

	//始点ノーツ
	if (isStart) {
		//始点ノーツ生成
		startNotes = new ShortNotes(x, y);

		//終点ノーツフラグ
		isStart = false;
		
		return nullptr;
	}
	//終点ノーツ
	else {
		//終点ノーツ生成
		endNotes = new ShortNotes(startNotes->position.x, y);
		
		//ロングノーツ生成
		LongNotes* longNotes = new LongNotes(*startNotes);
		//終点ノーツセット
		longNotes->SetEndNotes(*endNotes);
		
		//始点ノーツフラグ
		isStart = true;
		
		return longNotes;
	}
	//Notes* notes = new ShortNotes(x, y);
	//return notes;
}