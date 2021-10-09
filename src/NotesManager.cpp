#include "NotesManager.hpp"
#include "ShortNotes.hpp"
#include "INotesCreator.hpp"
#include "NotesData.hpp"
#include "Transform.hpp"
#include "InputDeviceContainer.hpp"
#include "DxLib.h"
#include <algorithm>

#define CREATE 0

//static変数実体化
NotesEditor::NOTESTYPE NotesEditor::NotesManager::type = NotesEditor::NOTESTYPE::SHORT_NOTES;

bool NotesEditor::NotesManager::IsExist(float x, float y)
{
	for (auto notes : notesList)
	{
		Engine::Components::Position pos = notes->GetTransform().GetPosition();
		if (pos.x == x && pos.y == y)
			return true;
	}
	return false;
}

NotesEditor::NotesManager::NotesManager() : color(GetColor(0, 255, 0))
{
}

void NotesEditor::NotesManager::ChangeNotesTypeShort()
{
	type = NOTESTYPE::SHORT_NOTES;
	color = GetColor(0, 255, 0);
	DrawFormatString(800, 600, GetColor(0, 255, 0), "ShortNotes");
}

void NotesEditor::NotesManager::ChangeNotesTypeLong()
{
	type = NOTESTYPE::LONG_NOTES;
	color = GetColor(0, 128, 255);
	DrawFormatString(800, 600, GetColor(0, 255, 0), "LongNotes");
}

void NotesEditor::NotesManager::ChangeNotesTypeSlide()
{
	type = NOTESTYPE::SLIDE_NOTES;
	color = GetColor(255, 128, 0);
	DrawFormatString(800, 600, GetColor(0, 255, 0), "SlideNotes");
}

void NotesEditor::NotesManager::Update()
{
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().IsPressKey(KEY_INPUT_Q))
		ShortNotes::playRange += 0.001f;
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().IsPressKey(KEY_INPUT_E))
		ShortNotes::playRange -= 0.001f;
}

void NotesEditor::NotesManager::Draw()
{
	DrawFormatString(800, 625, GetColor(0, 255, 0), "playRange:%f", ShortNotes::playRange);
}

void NotesEditor::NotesManager::CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList)
{
	/* ノーツ生成 */
	// 同じ場所にノーツが存在した
	if (IsExist(notesData.x, notesData.y))
		return;
	//ノーツ生成
	INotesCreator* creator = nullptr;

	//生成するノーツ
	switch (type)
	{
	case NOTESTYPE::SHORT_NOTES:
		creator = &shortNotesCreator;
		longNotesCreator.Cancel(objList);		//ロングノーツの設置をキャンセル
		//slideNotesCreator.Cancel(notesList);	//スライドノーツの設置をキャンセル
		break;
	case NOTESTYPE::LONG_NOTES:
		creator = &longNotesCreator;
		//slideNotesCreator.Cancel(notesList);	//スライドノーツの設置をキャンセル
		break;
	case NOTESTYPE::SLIDE_NOTES:
		creator = &slideNotesCreator;
		//longNotesCreator.Cancel(notesList);		//ロングノーツの設置をキャンセル
		break;
	default:
		break;
	}
	//ノーツ生成
	creator->CreateNotes(notesData,objList);
	//objList.push_back(notes);
	//notesList.push_back(notes);
}

void NotesEditor::NotesManager::DeleteNotes(float x, float y)
{
}

void NotesEditor::NotesManager::DeleteObj()
{
}
