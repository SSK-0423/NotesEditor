#include "SlideNotesCreator.hpp"
#include "NotesData.hpp"
#include "NotesColor.hpp"
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

NotesEditor::SlideNotesCreator::SlideNotesCreator() : isStart(true) ,slideNotes(nullptr)
{
}

NotesEditor::Notes* NotesEditor::SlideNotesCreator::CreateNotes(const NotesData& notesData)
{
	// Enterキーで決定するのを忘れがちなので、設置中はノーツの色をピンク・紫にしたい
	
	// 設置開始
	if (isStart)
	{
		isStart = false;

		//始点ノーツ生成
		ShortNotes* notes = new ShortNotes(notesData);
		notes->SetColor(NotesColor::puttingNotesColor);
		//スライドノーツのリストに追加
		slideNotesList.push_back(notes);
		//スライドノーツ生成
		slideNotes = new SlideNotes(slideNotesList);

		return slideNotes;
	}
	// 中間ノーツ設置
	else if (!isStart && notesData.y < slideNotesList[slideNotesList.size() - 1]->GetTransform().GetPosition().y)
	{
		// 中間ノーツ生成
		ShortNotes* notes = new ShortNotes(notesData);
		notes->SetColor(NotesColor::puttingNotesColor);
		// スライドノーツのリストに追加
		slideNotesList.push_back(notes);
		// スライドノーツのリスト更新
		slideNotes->AddNotes(*notes);

	}
	return nullptr;
}

void NotesEditor::SlideNotesCreator::IsEnd()
{
	// 設置完了
	if (slideNotesList.size() >= 4)
	{
		slideNotes->PutComplete();
		Init();
	}
}

void NotesEditor::SlideNotesCreator::Init()
{
	isStart = true;
	slideNotes = nullptr;
	slideNotesList.clear();
	slideNotesList.shrink_to_fit();
}

NotesEditor::Notes* NotesEditor::SlideNotesCreator::Cancel()
{
	Notes* cancelNotes = slideNotes;
	Init();
	return cancelNotes;
}