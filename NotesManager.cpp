#include "NotesManager.hpp"

//staticïœêîé¿ëÃâª
NOTESTYPE NotesManager::type;

void NotesManager::ChangeNotesTypeShort() noexcept {
	type = SHORT_NOTES;
}
void NotesManager::ChangeNotesTypeLong() noexcept {
	type = LONG_NOTES;
}
void NotesManager::ChangeNotesTypeSlide() noexcept {
	type = SLIDE_NOTES;
}
void NotesManager::CreateNotes(std::vector<GameObject*> objList) noexcept {
	//Notes* notes = new Notes();
	//notesList.push_back(notes);
	//objList.push_back((GameObject*)notes);
}