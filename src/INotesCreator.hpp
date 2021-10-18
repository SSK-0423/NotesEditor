#pragma once
#include <vector>

/*
* NotesCreatorのインターフェース
*/

namespace NotesEditor
{
	struct NotesData;
	class Notes;

	class INotesCreator {
	public:
		virtual Notes* CreateNotes(const NotesData& notesData) = 0;
	};
}