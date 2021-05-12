#include "NotesManager.hpp"
#include "ShortNotes.hpp"
#include "NotesCreator.hpp"
#include "ShortNotesCreator.hpp"
#include "LongNotesCreator.hpp"
#include "SlideNotesCreator.hpp"

//static�ϐ����̉�
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

//�m�[�c����
Notes NotesManager::CreateNotes(float& x, float& y) noexcept {
	//�m�[�c����
	NotesCreator* creator = nullptr;

	//��������m�[�c
	switch (type)
	{
		case SHORT_NOTES:
			creator = new ShortNotesCreator();
			break;
		case LONG_NOTES:
			creator = new LongNotesCreator();
		case SLIDE_NOTES:
			creator = new SlideNotesCreator();
		default:
			creator = new ShortNotesCreator();
			break;
	}

	return creator->CreateNotes(x,y);
}