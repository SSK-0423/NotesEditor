#include "NotesManager.hpp"
#include "ShortNotes.hpp"
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
void NotesManager::CreateNotes(std::vector<GameObject*>& objList,float& x, float& y) noexcept {
	ShortNotes* notes = new ShortNotes(x,y);
	objList.push_back((GameObject*)notes);
	//Notes* notes = new Notes();
	//notesList.push_back(notes);
	//objList.push_back((GameObject*)notes);
}