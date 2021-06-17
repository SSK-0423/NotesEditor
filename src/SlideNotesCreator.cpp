#include "SlideNotesCreator.hpp"
#include "SlideNotes.hpp"
#include "DxLib.h"
#include "KeyInput.hpp"
#include <algorithm>

SlideNotesCreator::SlideNotesCreator() noexcept {
	isEnd = false;
}

Notes* SlideNotesCreator::CreateNotes(float& x, float& y) noexcept {
	return nullptr;
}

void SlideNotesCreator::CreateNotes(std::vector<GameObject*>& objList) noexcept {
	if(isEnd){
		//スライドノーツ生成
		SlideNotes* slideNotes = new SlideNotes(slideNotesList);
		
		//設置途中に追加したノーツを削除
		for (int i = slideNotesList.size() - 1; i >= 0; i--) {
			objList.pop_back();
		}

		//ノーツリストにスライドノーツを追加する
		objList.push_back(slideNotes);
		slideNotesList.clear();
		isEnd = false;
	}
}

void SlideNotesCreator::CreateNotes(float& x, float& y, std::vector<GameObject*>& objList) noexcept
{
	//始点、中間点ノーツ
	if (!isEnd) {
		//始点
		if (slideNotesList.size() == 0) {
			//ノーツ生成
			ShortNotes* notes = new ShortNotes(x, y);
			notes->SetColor(GetColor(255, 128, 0));
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
			notes->SetColor(GetColor(255, 128, 0));
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
			endNotes->SetColor(GetColor(255, 128, 0));
			//スライドノーツのリストに追加
			slideNotesList.push_back(endNotes);

			//スライドノーツ生成
			SlideNotes* slideNotes = new SlideNotes(slideNotesList);

			//設置途中に追加したノーツを削除
			for (int i = slideNotesList.size() - 1; i >= 0; i--) {
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

void SlideNotesCreator::Cancel(std::vector<GameObject*>& objList) noexcept {
	for (int i = 0; i < slideNotesList.size(); i++) {
		objList.pop_back();
	}
	slideNotesList.clear();
}
