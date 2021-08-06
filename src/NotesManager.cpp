#include "NotesManager.hpp"
#include "ShortNotes.hpp"
#include "NotesCreator.hpp"
#include "ShortNotesCreator.hpp"
#include "LongNotesCreator.hpp"
#include "SlideNotesCreator.hpp"
#include "DxLib.h"
#include "KeyInput.hpp"
#include <algorithm>

#define CREATE 0

//static�ϐ����̉�
NOTESTYPE NotesManager::type;


NotesManager::NotesManager() noexcept {
	color = GetColor(0, 255, 0);
	//objList = nullptr;
}

//	�V���[�g�m�[�c�ɕύX
void NotesManager::ChangeNotesTypeShort() noexcept {
	type = SHORT_NOTES;
	color = GetColor(0, 255, 0);
}
//	�����O�m�[�c�ɕύX
void NotesManager::ChangeNotesTypeLong() noexcept {
	type = LONG_NOTES;
	color = GetColor(0, 128, 255);
}
//	�X���C�h�m�[�c�ɕύX
void NotesManager::ChangeNotesTypeSlide() noexcept {
	type = SLIDE_NOTES;
	color = GetColor(255, 128, 0);
}

void NotesManager::Update() noexcept {
	if (Key[KEY_INPUT_RETURN] == 1) {
		slideNotesCreator.IsEnd();
		slideNotesCreator.CreateNotes(notesList);
	}
}

void NotesManager::Draw() noexcept {
	int x, y;
	GetMousePoint(&x, &y);
	DrawBox(x - 10, y - 10, x + 10, y + 10, color, true);
	DrawFormatString(800, 350, GetColor(0, 255, 0), "NotesType:%d", type);
	DrawFormatString(800, 400, GetColor(0, 255, 0), "�m�[�c��:%d", notesList.size());
	slideNotesCreator.Draw();
}

std::vector<GameObject*>* NotesManager::GetListRef() noexcept {
	return &notesList;
}

//�m�[�c����
void NotesManager::CreateNotes(float& x, float& y) noexcept {

	if (IsExist(x, y)) {
		//�m�[�c����
		NotesCreator* creator = nullptr;

		//��������m�[�c
		switch (type)
		{
		case SHORT_NOTES:
			creator = &shortNotesCreator;
			longNotesCreator.Cancel(notesList);		//�����O�m�[�c�̐ݒu���L�����Z��
			slideNotesCreator.Cancel(notesList);	//�X���C�h�m�[�c�̐ݒu���L�����Z��
			break;
		case LONG_NOTES:
			creator = &longNotesCreator;
			slideNotesCreator.Cancel(notesList);	//�X���C�h�m�[�c�̐ݒu���L�����Z��
			break;
		case SLIDE_NOTES:
			creator = &slideNotesCreator;
			longNotesCreator.Cancel(notesList);		//�����O�m�[�c�̐ݒu���L�����Z��
			break;
		default:
			creator = &shortNotesCreator;
			break;
		}
		//�m�[�c����
		creator->CreateNotes(x, y, notesList);
	}
}

// �m�[�c�폜
void NotesManager::DeleteNotes(int& x, int& y) noexcept {
	for (auto notes : notesList) {
		if (notes->position.x - notes->GetObjWidth() / 2 <= x && notes->position.x + notes->GetObjWidth() / 2 >= x &&
			notes->position.y - notes->GetObjHeight() / 2 <= y && notes->position.y + notes->GetObjHeight() / 2 >= y) {
			auto deleteNotes = std::find(notesList.begin(), notesList.end(), notes);
			notesList.erase(deleteNotes);

			//�X���C�h�m�[�c�̒��ԃm�[�c�폜
			if (dynamic_cast<ShortNotes*>(notes) != nullptr) {
				if (dynamic_cast<ShortNotes*>(notes)->GetNotesColor() == GetColor(255, 128, 0)) {
					slideNotesCreator.DeleteNotes(*notes);
				}
				if (dynamic_cast<ShortNotes*>(notes)->GetNotesColor() == GetColor(0, 128, 255)) {
					longNotesCreator.DeleteNotes(*notes);
				}
				int clapHandle = LoadSoundMem("sounds/clap.ogg");
				PlaySoundMem(clapHandle, DX_PLAYTYPE_BACK);
			}
		}
	}
}

//	�����ꏊ�Ƀm�[�c��ݒu�ł��Ȃ��悤�ɂ���
bool NotesManager::IsExist(float& x, float& y) noexcept {
	for (auto notes : notesList) {
		if (notes->collisionPos.x == x && notes->collisionPos.y == y) {
			return false;
		}
	}
	return true;
}

//	�m�[�c�̑S�폜
void NotesManager::DeleteObj() noexcept {
	for (auto notes : notesList) {
		delete notes;
	}
	notesList.clear();
}