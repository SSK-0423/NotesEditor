#include "SlideNotesCreator.hpp"
#include "SlideNotes.hpp"
#include "Transform.hpp"
#include "DxLib.h"
#define CREATEMODE 1;
/*
	スライドノーツ設置仕様
	・最低4点必要
	・エンターキーを押すとそれで確定→isEnd
	・1点目を置いた時から、スライドノーツ生成して返す→スライドノーツ内で4点以上あるかどうかを判定する
	・1点目稼働かを判定する→isStart
	・設置中に点を削除するにはどうするか→スライドノーツ内のdeleteNotesを呼び出して、補間を再計算する
	・5点目以降は置くたびに補間が再計算され、描画が修正される
*/
NotesEditor::SlideNotesCreator::SlideNotesCreator() : isStart(true), isEnd(false)
{
}

NotesEditor::Notes* NotesEditor::SlideNotesCreator::CreateNotes(const NotesData& notesData)
{
	return nullptr;
}

NotesEditor::Notes* NotesEditor::SlideNotesCreator::CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList)
{
#ifdef CREATEMODE
	// 設置開始
	if (isStart)
	{
		isStart = false;

		//始点ノーツ生成
		ShortNotes* notes = new ShortNotes(notesData);
		notes->SetColor(GetColor(255, 128, 0));
		//スライドノーツのリストに追加
		slideNotesList.push_back(notes);		
		//スライドノーツ生成
		slideNotes = new SlideNotes(slideNotesList);
		//描画リストに追加
		objList.push_back(slideNotes);
		
		return slideNotes;
	}
	// 中間ノーツ設置
	else if (!isStart)
	{
		// 中間ノーツ生成
		ShortNotes* notes = new ShortNotes(notesData);
		notes->SetColor(GetColor(255, 128, 0));
		// スライドノーツのリストに追加
		slideNotesList.push_back(notes);
		// スライドノーツのリスト更新
		slideNotes->AddNotes(*notes);
	}
#else
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

#endif // CREATEMODE
	return nullptr;
}

void NotesEditor::SlideNotesCreator::IsEnd()
{
	// 設置完了
	if (slideNotesList.size() >= 4)
	{
		slideNotes = nullptr;
		slideNotesList.clear();
		slideNotesList.shrink_to_fit();
		isStart = true;
		isEnd = false;
	}
}

void NotesEditor::SlideNotesCreator::Cancel(std::vector<Engine::GameObject*>& objList)
{
	//for (int i = 0; i < slideNotesList.size(); i++)
	//{
	//	objList.pop_back();
	//}
	isStart = true;
	isEnd = false;
	slideNotesList.clear();
	slideNotesList.shrink_to_fit();
}

void NotesEditor::SlideNotesCreator::DeleteNotes(Engine::GameObject& notes)
{
}

void NotesEditor::SlideNotesCreator::Draw()
{
}
