#include "SlideNotesCreator.hpp"
#include "SlideNotes.hpp"
#include <algorithm>
//void SlideNotesCreator::CreateNotes(float& x, float& y) noexcept {
//	Notes* notes = new SlideNotes(x, y);
//}

SlideNotesCreator::SlideNotesCreator() noexcept {
	isEnd = false;
}

Notes* SlideNotesCreator::CreateNotes(float& x, float& y) noexcept {
	//Notes* notes = new SlideNotes(x, y);
	return nullptr;
}

void SlideNotesCreator::CreateNotes(float& x, float& y, std::vector<GameObject*>& objList) noexcept
{
	//始点、中間点ノーツ
	if (!isEnd) {
		//始点
		if (slideNotesList.size() == 0) {
			//ノーツ生成
			ShortNotes* notes = new ShortNotes(x, y);
			//スライドノーツのリストに追加
			slideNotesList.push_back(notes);
			//カメラ描画対象オブジェクトリストに追加
			objList.push_back(notes);
		}
		//中間点
		else if (slideNotesList.size() > 0 && y < slideNotesList[slideNotesList.size() - 1]->collisionPos.y) 
		{
			//ノーツ生成
			ShortNotes* notes = new ShortNotes(x, y);
			//スライドノーツのリストに追加
			slideNotesList.push_back(notes);
			//カメラ描画対象オブジェクトリストに追加
			objList.push_back(notes);
		}
	}
	//終点ノーツ
	else {
		//終点ノーツの位置が始点ノーツより後ろ(上)だったらノーツ設置
		if (y < slideNotesList[slideNotesList.size() - 1]->collisionPos.y) {
			//終点ノーツ生成
			ShortNotes* endNotes = new ShortNotes(x, y);
			//スライドノーツのリストに追加
			slideNotesList.push_back(endNotes);

			//スライドノーツ生成
			SlideNotes* slideNotes = new SlideNotes(x,y,slideNotesList);

			//設置途中に追加したノーツを削除
			for (int i = slideNotesList.size() - 2; i >= 0; i--) {
				objList.pop_back();
				//auto deleteNotes = std::find(slideNotesList.begin(), slideNotesList.end(), slideNotesList[i]);
				//objList.erase(deleteNotes);
			}

			//ノーツリストにスライドノーツを追加する
			//slideNotesList.push_back((GameObject*)slideNotes);
			//カメラ描画対象オブジェクトリストに追加する
			objList.push_back(slideNotes);
			slideNotesList.clear();
			isEnd = false;
		}
	}
}

// スライドノーツの終端を設置していいか判定
void SlideNotesCreator::IsEnd() noexcept {
	if (slideNotesList.size() >= 4) {
		isEnd = true;
	}
}
