#pragma once
#include <vector>

/*
* NotesCreator�̃C���^�[�t�F�[�X
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