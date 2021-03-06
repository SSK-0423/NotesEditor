#include "NotesManager.hpp"
#include "ShortNotesCreator.hpp"
#include "LongNotesCreator.hpp"
#include "SlideNotesCreator.hpp"
#include "NotesData.hpp"
#include "ShortNotes.hpp"
#include "Transform.hpp"
#include "InputDeviceContainer.hpp"
#include "NotesColor.hpp"
#include "FumenJsonGenerator.hpp"
#include "DxLib.h"
#include <algorithm>

float NotesEditor::NotesManager::beforeScale = 1.f;
NotesEditor::NOTESTYPE NotesEditor::NotesManager::type = NotesEditor::NOTESTYPE::SHORT_NOTES;

NotesEditor::NotesManager::NotesManager() : mousePointerColor(GetColor(0, 255, 0))
{
}

NotesEditor::NotesManager::~NotesManager()
{
	for (auto notes : notesList)
		delete notes;
	notesList.clear();
	notesList.shrink_to_fit();
}

void NotesEditor::NotesManager::ChangeNotesTypeShort()
{
	type = NOTESTYPE::SHORT_NOTES;
	mousePointerColor = NotesColor::shortNotesColor;
}

void NotesEditor::NotesManager::ChangeNotesTypeLong()
{
	type = NOTESTYPE::LONG_NOTES;
	mousePointerColor = NotesColor::longNotesColor;
}

void NotesEditor::NotesManager::ChangeNotesTypeSlide()
{
	type = NOTESTYPE::SLIDE_NOTES;
	mousePointerColor = NotesColor::slideNotesColor;
}

void NotesEditor::NotesManager::Update()
{
	// 次のスライドノーツ設置へ
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().IsPressKey(KEY_INPUT_RETURN))
		SlideNotesCreator::Instance().IsEnd();
}

void NotesEditor::NotesManager::Draw()
{
	int x, y;
	GetMousePoint(&x, &y);
	DrawBox(x - 10, y - 10, x + 10, y + 10, mousePointerColor, true);
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
		creator = &ShortNotesCreator::Instance();
		break;
	case NOTESTYPE::LONG_NOTES:
		creator = &LongNotesCreator::Instance();
		break;
	case NOTESTYPE::SLIDE_NOTES:
		creator = &SlideNotesCreator::Instance();
		break;
	default:
		break;
	}
	Cancel(type, objList);

	//ノーツ生成
	Notes* notes = creator->CreateNotes(notesData);

	//ノーツ追加
	if (notes != nullptr)
	{
		objList.push_back(notes);
		notesList.push_back(notes);
	}
}

void NotesEditor::NotesManager::DeleteNotes(float x, float y, std::vector<Engine::GameObject*>& objList)
{
	for (auto itr = notesList.begin(); itr != notesList.end(); itr++)
	{
		Notes* notes = *itr;
		bool isCol = notes->Collision(x, y);
		if (isCol)
		{
			notesList.erase(itr);
			auto notesDel = std::find(objList.begin(), objList.end(), static_cast<Engine::GameObject*>(notes));
			objList.erase(notesDel);

			// 削除したノーツがスライドノーツなら、ノーツ設置確定処理を行う
			// →slideNotesCreatorの初期化処理を行う
			NOTESTYPE notesType = notes->GetNotesType();
			if (notesType == NOTESTYPE::LONG_NOTES)
				LongNotesCreator::Instance().Init();
			else if (notesType == NOTESTYPE::SLIDE_NOTES)
				SlideNotesCreator::Instance().Init();

			break;
		}
	}
}

void NotesEditor::NotesManager::Delete()
{
	for (auto notes : notesList)
		delete notes;
	notesList.clear();
	notesList.shrink_to_fit();
}

void NotesEditor::NotesManager::ChangedNotesTransformByScale(float scale)
{
	if (beforeScale == scale) return;

	for (auto notes : notesList)
		notes->ChangedTransformByScale(scale, beforeScale < scale ? true : false);

	beforeScale = scale;
}

void NotesEditor::NotesManager::InitBeforeScale()
{
	beforeScale = 1.f;
}

NotesEditor::NOTESTYPE NotesEditor::NotesManager::GetPutNotesType()
{
	return type;
}

std::vector<NotesEditor::Notes*>& NotesEditor::NotesManager::GetNotesListRef()
{
	return notesList;
}

bool NotesEditor::NotesManager::IsExist(float x, float y)
{
	for (auto notes : notesList)
	{
		if (notes->Collision(x, y))
			return true;
	}
	return false;
}

void NotesEditor::NotesManager::Cancel(NOTESTYPE type, std::vector<Engine::GameObject*>& objList)
{
	Notes* notes = nullptr;

	switch (type)
	{
	case NOTESTYPE::SHORT_NOTES:
		notes = LongNotesCreator::Instance().Cancel();
		if (notes == nullptr)
			notes = SlideNotesCreator::Instance().Cancel();
		break;
	case NOTESTYPE::LONG_NOTES:
		notes = SlideNotesCreator::Instance().Cancel();
		break;
	case NOTESTYPE::SLIDE_NOTES:
		notes = LongNotesCreator::Instance().Cancel();
		break;
	default:
		break;
	}

	if (notes != nullptr)
	{
		auto deleteNotes = std::find(notesList.begin(), notesList.end(), notes);
		notesList.erase(deleteNotes);
		auto notesDel = std::find(objList.begin(), objList.end(), static_cast<Engine::GameObject*>(notes));
		objList.erase(notesDel);
	}
}