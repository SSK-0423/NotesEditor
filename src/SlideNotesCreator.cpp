#include "SlideNotesCreator.hpp"
#include "SlideNotes.hpp"
#include "Transform.hpp"
#include "DxLib.h"
//#include <algorithm>
//
//SlideNotesCreator::SlideNotesCreator()  {
//	isEnd = false;
//}
//
//Notes* SlideNotesCreator::CreateNotes(float& x, float& y)  {
//	return nullptr;
//}
//
//void SlideNotesCreator::CreateNotes(std::vector<GameObject*>& objList)  {
//	//終点ノーツ
//	if(isEnd){
//		//スライドノーツ生成
//		SlideNotes* slideNotes = new SlideNotes(slideNotesList);
//		
//		//設置途中に追加したノーツを削除
//		for (int i = slideNotesList.size() - 1; i >= 0; i--) {
//			objList.pop_back();
//		}
//
//		//ノーツリストにスライドノーツを追加する
//		objList.push_back(slideNotes);
//		//スライドノーツ設置用リスト初期化
//		slideNotesList.clear();
//		isEnd = false;
//	}
//}
//
//void SlideNotesCreator::CreateNotes(float& x, float& y, std::vector<GameObject*>& objList) 
//{
//	//始点、中間点ノーツ
//	if (!isEnd) {
//		//始点
//		if (slideNotesList.size() == 0) {
//			//ノーツ生成
//			ShortNotes* notes = new ShortNotes(x, y);
//			notes->SetColor(GetColor(255, 128, 0));
//			//スライドノーツのリストに追加
//			slideNotesList.push_back(notes);
//			//カメラ描画対象オブジェクトリストに追加
//			objList.push_back(notes);
//		}
//		//中間点
//		else if (slideNotesList.size() > 0 && y < slideNotesList[slideNotesList.size() - 1]->collisionPos.y) 
//		{
//			//ノーツ生成
//			ShortNotes* notes = new ShortNotes(x, y);
//			notes->SetColor(GetColor(255, 128, 0));
//			//スライドノーツのリストに追加
//			slideNotesList.push_back(notes);
//			//カメラ描画対象オブジェクトリストに追加
//			objList.push_back(notes);
//		}
//	}
//}
//
//// スライドノーツの終端を設置していいか判定
//void SlideNotesCreator::IsEnd()  {
//	if (slideNotesList.size() >= 4) {
//		isEnd = true;
//	}
//}
//
//// 設置キャンセル
//void SlideNotesCreator::Cancel(std::vector<GameObject*>& objList)  {
//	for (int i = 0; i < slideNotesList.size(); i++) {
//		objList.pop_back();
//	}
//	slideNotesList.clear();
//}
//
////中間ノーツ削除
//void SlideNotesCreator::DeleteNotes(GameObject& notes) 
//{
//	//スライドノーツの中間ノーツなら削除
//	auto deleteNotes = std::find(slideNotesList.begin(), slideNotesList.end(), (ShortNotes*)&notes);
//	slideNotesList.erase(deleteNotes);
//}
//
//void SlideNotesCreator::Draw()
//{
//	DrawFormatString(800, 600, GetColor(0, 255, 0), "スライドノーツリスト:%d", slideNotesList.size());
//}

NotesEditor::SlideNotesCreator::SlideNotesCreator() : isEnd(false)
{
}

NotesEditor::Notes* NotesEditor::SlideNotesCreator::CreateNotes(const NotesData& notesData)
{
	return nullptr;
}

NotesEditor::Notes* NotesEditor::SlideNotesCreator::CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList)
{
	//始点、中間点ノーツ
	if (!isEnd)
	{
		//始点
		if (slideNotesList.size() == 0) 
		{
			//ノーツ生成
			ShortNotes* notes = new ShortNotes(notesData);
			notes->SetColor(GetColor(255, 128, 0));
			//スライドノーツのリストに追加
			slideNotesList.push_back(notes);
			//カメラ描画対象オブジェクトリストに追加
			objList.push_back(notes);
		}
		//中間点
		else if (slideNotesList.size() > 0 && notesData.y < slideNotesList[slideNotesList.size() - 1]->GetTransform().GetPosition().y)
		{
			//ノーツ生成
			ShortNotes* notes = new ShortNotes(notesData);
			notes->SetColor(GetColor(255, 128, 0));
			//スライドノーツのリストに追加
			slideNotesList.push_back(notes);
			//カメラ描画対象オブジェクトリストに追加
			objList.push_back(notes);
			
			if (slideNotesList.size() >= 4)
				isEnd = true;
		}
	}

	//終点ノーツ
	if (isEnd)
	{
		//スライドノーツ生成
		SlideNotes* slideNotes = new SlideNotes(slideNotesList);

		//設置途中に追加したノーツを削除
		for (int i = slideNotesList.size() - 1; i >= 0; i--)
		{
			objList.pop_back();
		}

		//ノーツリストにスライドノーツを追加する
		objList.push_back(slideNotes);

		//スライドノーツ設置用リスト初期化
		slideNotesList.clear();
		slideNotesList.shrink_to_fit();
		
		//4点置いたら終点にしない
		isEnd = false;

		return slideNotes;
	}

	return nullptr;
}

void NotesEditor::SlideNotesCreator::IsEnd()
{
}

void NotesEditor::SlideNotesCreator::Cancel(std::vector<Engine::GameObject*>& objList)
{
	for (int i = 0; i < slideNotesList.size(); i++) 
	{
		objList.pop_back();
	}
	slideNotesList.clear();
	slideNotesList.shrink_to_fit();
}

void NotesEditor::SlideNotesCreator::DeleteNotes(Engine::GameObject& notes)
{
}

void NotesEditor::SlideNotesCreator::Draw()
{
}
