#include "ShortNotesCreator.hpp"
#include "ShortNotes.hpp"

NotesEditor::ShortNotesCreator::ShortNotesCreator()
{
}

NotesEditor::Notes* NotesEditor::ShortNotesCreator::CreateNotes(const NotesData& notesData)
{
	return new ShortNotes(notesData);
}