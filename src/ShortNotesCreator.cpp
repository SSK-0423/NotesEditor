#include "ShortNotesCreator.hpp"
#include "ShortNotes.hpp"

NotesEditor::Notes* NotesEditor::ShortNotesCreator::CreateNotes(const NotesData& notesData)
{
	return new ShortNotes(notesData);
}

void NotesEditor::ShortNotesCreator::CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList)
{
	Notes* notes = new ShortNotes(notesData);
	objList.push_back(notes);
}
