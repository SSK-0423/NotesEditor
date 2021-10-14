#include "LongNotesCreator.hpp"
#include "NotesData.hpp"
#include "ShortNotes.hpp"
#include "LongNotes.hpp"
#include "Transform.hpp"
#include "DxLib.h"

bool NotesEditor::LongNotesCreator::isStart = true;
NotesEditor::LongNotes* NotesEditor::LongNotesCreator::longNotes = nullptr;
NotesEditor::ShortNotes* NotesEditor::LongNotesCreator::startNotes = nullptr;

NotesEditor::LongNotesCreator::LongNotesCreator()
{
}

NotesEditor::LongNotesCreator::~LongNotesCreator()
{
}

NotesEditor::Notes* NotesEditor::LongNotesCreator::CreateNotes(const NotesData& notesData)
{
	// 終点ノーツ
	if (isStart)
	{
		startNotes = new ShortNotes(notesData);

		longNotes = new LongNotes(*startNotes);

		isStart = false;
		return longNotes;
	}
	//終点ノーツ
	//終点ノーツの位置が始点ノーツより後ろ(上)だったらロングノーツ設置
	if (notesData.y < startNotes->GetTransform().GetPosition().y) {
		//終点ノーツ生成
		ShortNotes* endNotes = new ShortNotes(notesData);
		//終点ノーツ追加
		longNotes->AddEndNotes(*endNotes);
		//始点ノーツフラグ
		isStart = true;
		//始点ノーツを無効にする
		startNotes = nullptr;
		//ロングノーツ初期化
		longNotes = nullptr;
	}

	return nullptr;
}

NotesEditor::Notes* NotesEditor::LongNotesCreator::Cancel()
{
	Notes* cancelNotes = longNotes;
	Init();
	return cancelNotes;
}

void NotesEditor::LongNotesCreator::Init()
{
	isStart = true;
	longNotes = nullptr;
	startNotes = nullptr;
}
