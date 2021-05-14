#include "NotesManager.hpp"
#include "ShortNotes.hpp"
#include "NotesCreator.hpp"
#include "ShortNotesCreator.hpp"
#include "LongNotesCreator.hpp"
#include "SlideNotesCreator.hpp"

//static�ϐ����̉�
NOTESTYPE NotesManager::type;

NotesManager::NotesManager() noexcept {
	barManager = nullptr;
}

NotesManager::NotesManager(BarManager& barManager) noexcept {
	this->barManager = &barManager;
}

void NotesManager::SetBarManager(BarManager& barManager) noexcept {
	this->barManager = &barManager;
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

void NotesManager::Update() noexcept {
	
}

//�m�[�c����
Notes* NotesManager::CreateNotes(float& x, float& y) noexcept {
	//�m�[�c����
	NotesCreator* creator = nullptr;

	//��������m�[�c
	switch (type)
	{
		case SHORT_NOTES:
			creator = new ShortNotesCreator();
			break;
		case LONG_NOTES:
			creator = new LongNotesCreator(*barManager);
			break;
		case SLIDE_NOTES:
			creator = new SlideNotesCreator();
			break;
		default:
			creator = new ShortNotesCreator();
			break;
	}

	return creator->CreateNotes(x,y);
}