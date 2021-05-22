#include "NotesManager.hpp"
#include "ShortNotes.hpp"
#include "NotesCreator.hpp"
#include "ShortNotesCreator.hpp"
#include "LongNotesCreator.hpp"
#include "SlideNotesCreator.hpp"
#include "DxLib.h"
#include <algorithm>

#define CREATE 0

//static変数実体化
NOTESTYPE NotesManager::type;


NotesManager::NotesManager() noexcept {
	objList = nullptr;
}

void NotesManager::ChangeNotesTypeShort() noexcept {
	type = SHORT_NOTES;
}
void NotesManager::ChangeNotesTypeLong() noexcept {
	type = LONG_NOTES;
}
void NotesManager::ChangeNotesTypeSlide() noexcept {
	type = SLIDE_NOTES;
}

void NotesManager::SetObjList(std::vector<GameObject*>& objList) noexcept {
	this->objList = &objList;
}
void NotesManager::Update() noexcept {

}

void NotesManager::Draw() noexcept {
	DrawFormatString(800, 350, GetColor(0, 255, 0), "NotesType:%d", type);
	DrawFormatString(800, 400, GetColor(0, 255, 0), "ノーツ数:%d", notesList.size());
}

//ノーツ生成
void NotesManager::CreateNotes(float& x, float& y) noexcept {

	if (IsExist(x, y)) {
		if (CREATE == 1) {
			//ノーツ生成
			NotesCreator* creator = nullptr;

			//生成するノーツ
			switch (type)
			{
			case SHORT_NOTES:
				creator = &shortNotesCreator;
				break;
			case LONG_NOTES:
				creator = &longNotesCreator;
				break;
			case SLIDE_NOTES:
				creator = &slideNotesCreator;
				break;
			default:
				creator = &shortNotesCreator;
				break;
			}

			Notes* notes = creator->CreateNotes(x, y);
			if (notes != nullptr) {
				notesList.push_back(notes);
				objList->push_back(notes);
			}
		}
		else {
			//ノーツ生成
			NotesCreator* creator = nullptr;

			//生成するノーツ
			switch (type)
			{
			case SHORT_NOTES:
				creator = &shortNotesCreator;
				break;
			case LONG_NOTES:
				creator = &longNotesCreator;
				break;
			case SLIDE_NOTES:
				creator = &slideNotesCreator;
				break;
			default:
				creator = &shortNotesCreator;
				break;
			}
			creator->CreateNotes(x, y, *objList);
		}
	}
}

void NotesManager::DeleteNotes(float& x, float& y) noexcept {
	for (auto notes : notesList) {
		if (notes->position.x == x && notes->position.y == y) {
			auto deleteNotes = std::find(notesList.begin(), notesList.end(), notes);
			notesList.erase(deleteNotes);
		}
	}
}

bool NotesManager::IsExist(float& x, float& y) noexcept {
	for (auto notes : notesList) {
		if (notes->collisionPos.x == x && notes->collisionPos.y == y) {
			return false;
		}
	}
	return true;
}
void NotesManager::DeleteObj() noexcept {
	notesList.clear();
}