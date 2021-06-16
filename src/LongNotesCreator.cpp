#include "LongNotesCreator.hpp"

//クラス変数実体化
bool LongNotesCreator::isStart = true;

LongNotesCreator::LongNotesCreator() noexcept {
	startNotes = nullptr;
	endNotes = nullptr;
}

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
		//終点ノーツの位置が始点ノーツより前だったらnullを返す
		if (y > startNotes->collisionPos.y) {
			return nullptr;
		}
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

void LongNotesCreator::CreateNotes(float& x, float& y, std::vector<GameObject*>& objList) noexcept {
	//始点ノーツ
	if (isStart) {
		//始点ノーツ生成
		startNotes = new ShortNotes(x, y);

		//終点ノーツフラグ
		isStart = false;

		objList.push_back(startNotes);
	}
	//終点ノーツ
	else {
		//終点ノーツの位置が始点ノーツより後ろ(上)だったらロングノーツ設置
		if (y < startNotes->collisionPos.y) {
			//終点ノーツ生成
			endNotes = new ShortNotes(startNotes->collisionPos.x, y);

			//ロングノーツ生成
			LongNotes* longNotes = new LongNotes(*startNotes,*endNotes);

			//始点ノーツフラグ
			isStart = true;
			//末尾に追加されている始点ノーツをリストから削除
			objList.pop_back();
			//ロングノーツ追加
			objList.push_back(longNotes);
		}
	}
}