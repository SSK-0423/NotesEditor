#include "LongNotesCreator.hpp"
#include "Transform.hpp"
#include "DxLib.h"

bool NotesEditor::LongNotesCreator::isStart = true;
NotesEditor::ShortNotes* NotesEditor::LongNotesCreator::startNotes = nullptr;
NotesEditor::ShortNotes* NotesEditor::LongNotesCreator::endNotes = nullptr;

NotesEditor::LongNotesCreator::LongNotesCreator()
{
}

NotesEditor::LongNotesCreator::~LongNotesCreator()
{
}

NotesEditor::Notes* NotesEditor::LongNotesCreator::CreateNotes(const NotesData& notesData)
{
	return nullptr;
}

void NotesEditor::LongNotesCreator::CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList)
{
	//始点ノーツ
	if (isStart) 
	{
		//始点ノーツ生成
		startNotes = new ShortNotes(notesData);
		startNotes->SetColor(GetColor(0, 128, 255));

		//終点ノーツフラグ
		isStart = false;

		objList.push_back(startNotes);

		return;
	}

	//終点ノーツ
	//終点ノーツの位置が始点ノーツより後ろ(上)だったらロングノーツ設置
	if (notesData.y < startNotes->GetTransform().GetPosition().y) {
		//終点ノーツ生成
		NotesData data(startNotes->GetTransform().GetPosition().x, notesData.y, notesData.lane, notesData.timing);
		endNotes = new ShortNotes(data);
		endNotes->SetColor(GetColor(0, 128, 255));
		//ロングノーツ生成
		LongNotes* longNotes = new LongNotes(*startNotes, *endNotes);

		//始点ノーツフラグ
		isStart = true;
		//末尾に追加されている始点ノーツをリストから削除
		objList.pop_back();
		//ロングノーツ追加
		objList.push_back(longNotes);
		//始点ノーツを無効にする
		startNotes = nullptr;
	}
}

void NotesEditor::LongNotesCreator::Cancel(std::vector<Engine::GameObject*>& objList)
{
	if (startNotes != nullptr)
	{
		objList.pop_back();
		isStart = true;
		delete startNotes;
		startNotes = nullptr;
	}
}

void NotesEditor::LongNotesCreator::DeleteNotes(Engine::GameObject& notes)
{

}
