#include "Notes.hpp"
#include "DxLib.h"

float NotesEditor::Notes::GetTiming()  
{
	return timing;
}

int NotesEditor::Notes::GetLane()  
{
	return lane;
}

NotesEditor::NOTESTYPE NotesEditor::Notes::GetNotesType()
{
	return type;
}