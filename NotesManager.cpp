#include "NotesManager.hpp"
#include "ShortNotes.hpp"
#include "NotesCreator.hpp"
#include "ShortNotesCreator.hpp"
#include "LongNotesCreator.hpp"
#include "SlideNotesCreator.hpp"
#include "DxLib.h"
//static�ϐ����̉�
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
	DrawFormatString(800, 700, GetColor(0, 255, 0), "NotesType:%d", type);
}

//�m�[�c����
void NotesManager::CreateNotes(float& x, float& y) noexcept {
	//�m�[�c����
	NotesCreator* creator = nullptr;

	//��������m�[�c
	switch (type)
	{
		case SHORT_NOTES:
			//creator = new ShortNotesCreator();
			creator = &shortNotesCreator;
			break;
		case LONG_NOTES:
			//creator = new LongNotesCreator();
			creator = &longNotesCreator;
			break;
		case SLIDE_NOTES:
			//creator = new SlideNotesCreator();
			creator = &slideNotesCreator;
			break;
		default:
			//creator = new ShortNotesCreator();
			creator = &shortNotesCreator;
			break;
	}

	Notes* notes = creator->CreateNotes(x, y);
	if (notes != nullptr) {
		objList->push_back(notes);
	}
}