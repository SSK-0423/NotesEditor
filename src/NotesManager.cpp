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

//static変数実体化
NOTESTYPE NotesManager::type;


NotesManager::NotesManager() noexcept {
	color = GetColor(0, 255, 0);
	//objList = nullptr;
}

//	ショートノーツに変更
void NotesManager::ChangeNotesTypeShort() noexcept {
	type = SHORT_NOTES;
	color = GetColor(0, 255, 0);
}
//	ロングノーツに変更
void NotesManager::ChangeNotesTypeLong() noexcept {
	type = LONG_NOTES;
	color = GetColor(0, 128, 255);
}
//	スライドノーツに変更
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
	DrawFormatString(800, 400, GetColor(0, 255, 0), "ノーツ数:%d", notesList.size());
	slideNotesCreator.Draw();
}

std::vector<GameObject*>* NotesManager::GetListRef() noexcept {
	return &notesList;
}

//ノーツ生成
void NotesManager::CreateNotes(float& x, float& y) noexcept {

	if (IsExist(x, y)) {
		//ノーツ生成
		NotesCreator* creator = nullptr;

		//生成するノーツ
		switch (type)
		{
		case SHORT_NOTES:
			creator = &shortNotesCreator;
			longNotesCreator.Cancel(notesList);		//ロングノーツの設置をキャンセル
			slideNotesCreator.Cancel(notesList);	//スライドノーツの設置をキャンセル
			break;
		case LONG_NOTES:
			creator = &longNotesCreator;
			slideNotesCreator.Cancel(notesList);	//スライドノーツの設置をキャンセル
			break;
		case SLIDE_NOTES:
			creator = &slideNotesCreator;
			longNotesCreator.Cancel(notesList);		//ロングノーツの設置をキャンセル
			break;
		default:
			creator = &shortNotesCreator;
			break;
		}
		//ノーツ生成
		creator->CreateNotes(x, y, notesList);
	}
}

// ノーツ削除
void NotesManager::DeleteNotes(int& x, int& y) noexcept {
	for (auto notes : notesList) {
		if (notes->position.x - notes->GetObjWidth() / 2 <= x && notes->position.x + notes->GetObjWidth() / 2 >= x &&
			notes->position.y - notes->GetObjHeight() / 2 <= y && notes->position.y + notes->GetObjHeight() / 2 >= y) {
			auto deleteNotes = std::find(notesList.begin(), notesList.end(), notes);
			notesList.erase(deleteNotes);

			//スライドノーツの中間ノーツ削除
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

//	同じ場所にノーツを設置できないようにする
bool NotesManager::IsExist(float& x, float& y) noexcept {
	for (auto notes : notesList) {
		if (notes->collisionPos.x == x && notes->collisionPos.y == y) {
			return false;
		}
	}
	return true;
}

//	ノーツの全削除
void NotesManager::DeleteObj() noexcept {
	for (auto notes : notesList) {
		delete notes;
	}
	notesList.clear();
}