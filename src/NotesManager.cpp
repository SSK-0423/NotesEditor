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
		if (notes->Collision(x, y))
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
	DrawFormatString(800, 600, GetColor(0, 255, 0), "notesList:%d", notesList.size());
	DrawFormatString(800, 575, GetColor(0, 255, 0), "isStart:%d", LongNotesCreator::isStart);
	DrawFormatString(800, 550, GetColor(0, 255, 0), "startNotes:%p", LongNotesCreator::startNotes);
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
		slideNotesCreator.Cancel(objList);	//スライドノーツの設置をキャンセル
		break;
	case NOTESTYPE::LONG_NOTES:
		creator = &longNotesCreator;
		slideNotesCreator.Cancel(objList);	//スライドノーツの設置をキャンセル
		break;
	case NOTESTYPE::SLIDE_NOTES:
		creator = &slideNotesCreator;
		longNotesCreator.Cancel(objList);		//ロングノーツの設置をキャンセル
		break;
	default:
		break;
	}

	//ノーツ生成
	Notes* notes = creator->CreateNotes(notesData, objList);

	//生成が完了していたらnotesListに追加
	if (notes != nullptr)
		notesList.push_back(notes);
}

void NotesEditor::NotesManager::DeleteNotes(float x, float y, std::vector<Engine::GameObject*>& objList)
{
	for (auto notes : notesList)
	{
		bool isCol = notes->Collision(x, y);
		if (isCol)
		{
			DrawFormatString(800, 500, GetColor(0, 255, 0), "当たった");
			auto deleteNotes = std::find(notesList.begin(), notesList.end(), notes);
			notesList.erase(deleteNotes);
			auto notesDel = std::find(objList.begin(), objList.end(), static_cast<Engine::GameObject*>(notes));
			objList.erase(notesDel);
		}
	}
}

void NotesEditor::NotesManager::DeleteObj()
{
}

NotesEditor::NOTESTYPE NotesEditor::NotesManager::GetPutNotesType()
{
	return type;
}
